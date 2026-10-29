"""Reprocessa tempos existentes, separadamente por imagem e versão, sem medições."""
import argparse
import hashlib
import json
import sys
from pathlib import Path
import pandas as pd
sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
from experimentos.analise_professor import analisar

if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--dados',type=Path,required=True)
    p.add_argument('--saida',type=Path,required=True)
    args=p.parse_args()
    if args.saida.exists(): raise FileExistsError('Use uma pasta nova.')
    protocolo=json.loads((args.dados/'protocolo.json').read_text())
    if protocolo['R']!=30: raise ValueError('A reanalise exige coleta R=30.')
    args.saida.mkdir(parents=True)
    resumo=[];origens=[]
    for item in protocolo['imagens']:
        imagem_id=item['id'];raw_path=args.dados/imagem_id/'tempos_brutos.csv'
        raw=pd.read_csv(raw_path,sep=';')
        if set(raw.variante)!={'baseline','unrolling'}: raise ValueError('Faltam versões.')
        if not (raw.groupby(['variante','n','k']).size()==30).all(): raise ValueError('Coleta incompleta.')
        origens.append(dict(imagem_id=imagem_id,arquivo=str(raw_path),sha256=hashlib.sha256(raw_path.read_bytes()).hexdigest()))
        for name,g in raw.groupby('variante'):
            dest=args.saida/imagem_id/name;dest.mkdir(parents=True)
            frame=analisar(g,dest,sorted(g.k.unique()))
            frame['variante']=name;frame['imagem_id']=imagem_id;frame['imagem_fonte']=item['arquivo']
            resumo.append(frame)
    pd.concat(resumo,ignore_index=True).to_csv(args.saida/'resultados_foca_aluno.csv',index=False,sep=';',decimal=',')
    (args.saida/'origem.json').write_text(json.dumps(origens,indent=2,ensure_ascii=False))
