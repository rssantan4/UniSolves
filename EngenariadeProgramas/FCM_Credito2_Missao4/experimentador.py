"""Bancada FCM real; secões e análise derivadas do notebook oficial preservado.
Use --modo smoke para ensaio separado; coleta R=30 é o padrão.
"""
import argparse
import csv
import hashlib
import importlib.metadata
import json
import platform
import random
import subprocess
import sys
import time
from datetime import datetime
from pathlib import Path
from zoneinfo import ZoneInfo
import numpy as np
import pandas as pd
from PIL import Image
from src.fcm_baseline import fcm_puro as baseline
from src.fcm_unrolling import fcm_puro as unrolling
from experimentos.analise_professor import analisar

ROOT=Path(__file__).resolve().parent
FUNCOES={'baseline':baseline,'unrolling':unrolling}

# 1. Função do aluno: o cronômetro chama diretamente o FCM de listas Python.
def preparar_rgb(imagem):
    pixels=np.asarray(imagem.convert('RGB'),dtype=np.float64).reshape(-1,3).tolist()
    if not pixels or any(len(p)!=3 for p in pixels):
        raise ValueError('A Missao 4 exige RGB com exatamente tres canais.')
    return pixels


def visualizar(C,U,shape,destino):
    U=np.asarray(U); labels=U.argmax(axis=1)
    rgb=np.rint(np.asarray(C)[labels]).clip(0,255).astype(np.uint8).reshape(*shape,3)
    Image.fromarray(rgb).save(destino/'segmentada.png')
    Image.fromarray(np.rint(U.max(axis=1).reshape(shape)*255).astype(np.uint8)).save(destino/'confianca.png')


def coletar_imagem(args):
    if args.saida.exists():
        raise FileExistsError('Escolha uma pasta nova: coletas existentes nunca sao sobrescritas.')
    args.saida.mkdir(parents=True)
    params=dict(m=2.0,max_iter=100,epsilon=0.01)
    R=5 if args.modo=='smoke' else 30
    sizes=[8,12] if args.modo=='smoke' else args.lados
    now=datetime.now(ZoneInfo('America/Bahia')).isoformat()
    def comando(cmd):
        try:
            result=subprocess.run(cmd,capture_output=True,text=True)
        except OSError:
            return 'nao aferido: comando indisponivel'
        return result.stdout.strip() if result.returncode==0 else 'nao aferido: comando falhou'
    env=dict(data_inicio=now,modo=args.modo,R=R,seed=42,parametros=params,lados=sizes,K=[2,3,4],
             maquina=platform.machine(),sistema=platform.platform(),python=sys.version,
             hardware=comando(['sysctl','-n','machdep.cpu.brand_string']),
             memoria_bytes=comando(['sysctl','-n','hw.memsize']),
             energia='nao aferido',implementacao=platform.python_implementation(),
             dependencias={p:importlib.metadata.version(p) for p in ('numpy','scipy','pandas','matplotlib','Pillow')},
             imagem_sha256=hashlib.sha256(args.imagem.read_bytes()).hexdigest(),
             imagem=str(args.imagem.name),redimensionamento='RGB Pillow Resampling.LANCZOS para quadrados',
             fontes_sha256={p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in (ROOT/'src').glob('fcm_*.py')},
             ordem='baseline/unrolling alternados por repeticao; aquecimento 1 por caso e versao',
             gc='padrao CPython; nao desativado',timer='perf_counter, chamada FCM completa; semente fora do timer')
    (args.saida/'ambiente.json').write_text(json.dumps(env,indent=2,ensure_ascii=False))
    # 2. Descoberta e ordenação: mesma imagem redimensionada, sem imagens sintéticas.
    with Image.open(args.imagem) as im:
        imagem=im.convert('RGB')
    with (args.saida/'tempos_brutos.csv').open('w',newline='') as handle:
        fields=['variante','n','k','repeticao','tempo','ordem','arquivo']
        writer=csv.DictWriter(handle,fieldnames=fields,delimiter=';'); writer.writeheader()
        # 3. Execução: imagem e AoS preparados uma vez por n, fora do cronômetro.
        for side in sorted(sizes):
            im=imagem.resize((side,side),Image.Resampling.LANCZOS)
            X=preparar_rgb(im); n=len(X)
            dest=args.saida/f'entrada_{side}.png'; im.save(dest)
            for K in (2,3,4):
                print(f'{args.modo}: n={n}, K={K}, R={R}',flush=True)
                for f in FUNCOES.values():
                    random.seed(42); f(X,K,**params)
                for r in range(R):
                    names=list(FUNCOES) if r%2==0 else list(reversed(FUNCOES))
                    for order,name in enumerate(names):
                        f=FUNCOES[name]
                        random.seed(42)
                        t0=time.perf_counter()
                        C,U=f(X,K,**params)
                        t1=time.perf_counter()
                        writer.writerow(dict(variante=name,n=n,k=K,repeticao=r,tempo=t1-t0,
                                             ordem=order,arquivo=dest.name)); handle.flush()
    # Auditoria da convergência em execução separada, sem contaminar medições.
    sys.path.insert(0,str(ROOT/'tests'))
    from test_fcm import executar_rastreado
    trajectories=[]
    for side in sorted(sizes):
        X=preparar_rgb(imagem.resize((side,side),Image.Resampling.LANCZOS))
        for K in (2,3,4):
            records=[]
            for name,f in FUNCOES.items():
                (C,U),hist=executar_rastreado(f,X,K,**params)
                records.append((C,U,hist))
                trajectories.append(dict(variante=name,n=len(X),k=K,I=len(hist),
                    delta_final=hist[-1]['max_diff'],convergiu=hist[-1]['max_diff']<params['epsilon']))
                visual=args.saida/name/f'visual_{side}_k{K}'; visual.mkdir(parents=True)
                visualizar(C,U,(side,side),visual)
            if records[0]!=records[1]: raise AssertionError('Divergencia funcional na entrada experimental')
    pd.DataFrame(trajectories).to_csv(args.saida/'convergencia.csv',index=False,sep=';')
    env['data_fim']=datetime.now(ZoneInfo('America/Bahia')).isoformat()
    (args.saida/'ambiente.json').write_text(json.dumps(env,indent=2,ensure_ascii=False))
    # 4-7. Filtragem P5/P95, CV estrito, curve_fit, 2D, 3D e CSV do professor.
    raw=pd.read_csv(args.saida/'tempos_brutos.csv',sep=';')
    summaries=[]
    for name,g in raw.groupby('variante'):
        dest=args.saida/name; dest.mkdir(exist_ok=True)
        summary=analisar(g.copy(),dest,[2,3,4]); summary['variante']=name; summaries.append(summary)
    all_summary=pd.concat(summaries)
    all_summary.to_csv(args.saida/'resultados_foca_aluno.csv',index=False,sep=';',decimal=',')
    a=all_summary[all_summary.variante=='baseline']; b=all_summary[all_summary.variante=='unrolling']
    comp=a.merge(b,on=['n','k'],suffixes=('_baseline','_unrolling'))
    comp['speedup']=comp.tempo_medio_baseline/comp.tempo_medio_unrolling
    comp['reducao_percentual']=100*(1-1/comp.speedup)
    comp['comparacao_homologada']=comp.estavel_CV_menor_15_baseline & comp.estavel_CV_menor_15_unrolling
    comp.to_csv(args.saida/'comparacao.csv',index=False,sep=';',decimal=',')
    # Pares brutos preservados separadamente: filtro independente altera pareamento.
    pairs=raw.pivot(index=['n','k','repeticao'],columns='variante',values='tempo').reset_index()
    pairs['speedup_par']=pairs.baseline/pairs.unrolling
    pairs.to_csv(args.saida/'comparacao_pares_brutos.csv',index=False,sep=';')
    plotar_comparacao(comp,args.saida/'comparacao.png')
    print('Coleta concluida:',args.saida,flush=True)


def plotar_comparacao(comp, destino):
    """Exibe todos os pares e assinala os que falharam no CV."""
    import matplotlib.pyplot as plt
    fig,ax=plt.subplots(figsize=(8,4))
    for K,g in comp.groupby('k'): ax.plot(g.n,g.speedup,'o-',label=f'K={K}')
    falhas=comp[~comp.comparacao_homologada]
    if not falhas.empty:
        ax.scatter(falhas.n,falhas.speedup,color='red',marker='x',s=80,zorder=5,label='Par nao homologado (CV)')
    ax.axhline(1,color='black',lw=1); ax.set(xlabel='Pixels (n)',ylabel='Tempo baseline / tempo unrolling',title='Comparacao descritiva na bancada local')
    ax.legend(); fig.tight_layout(); fig.savefig(destino,dpi=180); plt.close(fig)


def descobrir_imagens(pasta):
    """Aceita somente as duas fontes autorizadas, identificadas por nome e SHA-256."""
    autorizadas=json.loads((ROOT/'documentacao/imagens_autorizadas.json').read_text())
    arquivos=sorted(p for p in pasta.iterdir() if p.is_file() and p.suffix.lower() in
                    {'.png','.jpg','.jpeg','.bmp','.tif','.tiff','.webp'})
    if {p.name for p in arquivos}!={item['arquivo'] for item in autorizadas}:
        raise ValueError('A pasta deve conter exclusivamente as duas imagens autorizadas.')
    for item in autorizadas:
        p=pasta/item['arquivo']
        if hashlib.sha256(p.read_bytes()).hexdigest()!=item['sha256']:
            raise ValueError(f"Imagem diferente da fonte autorizada: {p.name}")
    return [(item,pasta/item['arquivo']) for item in autorizadas]


def coletar(args):
    fontes=descobrir_imagens(args.imagens_dir)
    if args.saida.exists():
        raise FileExistsError('Escolha pasta nova; nenhuma coleta e sobrescrita.')
    args.saida.mkdir(parents=True)
    protocolo=dict(imagens=[{k:v for k,v in item.items() if k!='origem'} for item,_ in fontes],
                   modo=args.modo,R=5 if args.modo=='smoke' else 30,
                   lados=[8,12] if args.modo=='smoke' else sorted(args.lados),
                   agrupamento=['imagem_id','variante','n','k'])
    (args.saida/'protocolo.json').write_text(json.dumps(protocolo,indent=2,ensure_ascii=False))
    for item,path in fontes:
        print('Fonte autorizada:',item['id'],path.name,flush=True)
        local=argparse.Namespace(**{**vars(args),'imagem':path,'saida':args.saida/item['id']})
        coletar_imagem(local)
    # Consolida sem agregar: cada identidade de imagem continua sendo uma serie distinta.
    for arquivo,decimal in [('tempos_brutos.csv','.'),('convergencia.csv','.'),
                            ('resultados_foca_aluno.csv',','),('comparacao.csv',','),
                            ('comparacao_pares_brutos.csv','.')]:
        partes=[]
        for item,_ in fontes:
            frame=pd.read_csv(args.saida/item['id']/arquivo,sep=';',decimal=decimal)
            frame.insert(0,'imagem_id',item['id']);frame.insert(1,'imagem_fonte',item['arquivo'])
            partes.append(frame)
        pd.concat(partes,ignore_index=True).to_csv(args.saida/arquivo,index=False,sep=';',decimal=decimal)
    print('Duas imagens concluidas, series separadas em:',args.saida,flush=True)


if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--modo',choices=['smoke','coleta'],default='coleta')
    p.add_argument('--imagens-dir',type=Path,default=ROOT/'minhas_imagens')
    p.add_argument('--saida',type=Path,required=True)
    p.add_argument('--lados',type=int,nargs='+',default=[16,24,32,48,64])
    args=p.parse_args()
    if len(set(args.lados))<2 or min(args.lados)<2: p.error('Use pelo menos dois lados distintos >=2.')
    coletar(args)
