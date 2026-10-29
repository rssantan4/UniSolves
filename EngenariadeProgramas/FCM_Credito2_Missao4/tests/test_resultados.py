"""Audita os CSV reais sem refazer medições; não fabrica tempos experimentais."""
import json
import unittest
from pathlib import Path
import numpy as np
import pandas as pd

ROOT=Path(__file__).resolve().parents[1]
DATA=ROOT/'resultados/coleta_duas_imagens_R30'

@unittest.skipUnless((DATA/'comparacao.csv').exists(),'Coleta local R30 ausente')
class TestResultados(unittest.TestCase):
    def test_integridade_estatistica_e_filtro(self):
        for imagem_id in ('imagem_01','imagem_02'):
            with self.subTest(imagem=imagem_id):
                self.verificar_estatistica(DATA/imagem_id)

    def verificar_estatistica(self, data):
        raw=pd.read_csv(data/'tempos_brutos.csv',sep=';')
        summary=pd.read_csv(data/'resultados_foca_aluno.csv',sep=';',decimal=',')
        self.assertEqual(len(raw),900)
        self.assertEqual(len(summary),30)
        self.assertTrue(np.isfinite(raw.tempo).all() and (raw.tempo>0).all())
        for (version,n,k),g in raw.groupby(['variante','n','k']):
            with self.subTest(variante=version,n=n,k=k):
                self.assertEqual(sorted(g.repeticao),list(range(30)))
                q=g.tempo.quantile([.05,.95]); valid=g[g.tempo.between(q.iloc[0],q.iloc[1])]
                s=summary[(summary.variante==version)&(summary.n==n)&(summary.k==k)].iloc[0]
                filtered=pd.read_csv(data/version/'tempos_filtrados.csv',sep=';',decimal=',')
                f=filtered[(filtered.n==n)&(filtered.k==k)]
                self.assertEqual(sorted(f.repeticao),sorted(valid.repeticao))
                self.assertEqual(s.contagem_valida,len(valid))
                self.assertAlmostEqual(s.tempo_medio,valid.tempo.mean(),places=12)
                self.assertAlmostEqual(s.desvio,valid.tempo.std(ddof=1),places=12)
                self.assertAlmostEqual(s.CV,valid.tempo.std(ddof=1)/valid.tempo.mean(),places=12)
                self.assertEqual(bool(s.estavel_CV_menor_15),s.CV<.15)
                self.assertAlmostEqual(s.taxa_descarte,1-len(valid)/30,places=12)

    def test_comparacao_e_modelo(self):
        for imagem_id in ('imagem_01','imagem_02'):
            with self.subTest(imagem=imagem_id):
                self.verificar_modelo(DATA/imagem_id)

    def verificar_modelo(self, data_dir):
        comp=pd.read_csv(data_dir/'comparacao.csv',sep=';',decimal=',')
        self.assertEqual(len(comp),15)
        np.testing.assert_allclose(comp.speedup,comp.tempo_medio_baseline/comp.tempo_medio_unrolling)
        for version in ['baseline','unrolling']:
            data=pd.read_csv(data_dir/version/'resultados_foca_aluno.csv',sep=';',decimal=',')
            model=json.loads((data_dir/version/'ajuste.json').read_text())
            a,b,c,d=model['coeficientes'].values()
            prediction=a*data.n*data.k+b*data.n+c*data.k+d
            np.testing.assert_allclose(data.tempo_predito,prediction,atol=1e-12)
            residual=data.tempo_medio-prediction
            r2=1-np.sum(residual**2)/np.sum((data.tempo_medio-data.tempo_medio.mean())**2)
            self.assertAlmostEqual(r2,model['r2'],places=12)
        env=json.loads((data_dir/'ambiente.json').read_text())
        self.assertEqual(env['R'],30)
        self.assertEqual(env['modo'],'coleta')
        trace=pd.read_csv(data_dir/'convergencia.csv',sep=';')
        self.assertTrue(trace.convergiu.all())
        a=trace[trace.variante=='baseline'].drop(columns='variante').reset_index(drop=True)
        b=trace[trace.variante=='unrolling'].drop(columns='variante').reset_index(drop=True)
        pd.testing.assert_frame_equal(a,b)

    def test_consolidacao_preserva_identidade_da_imagem(self):
        raw=pd.read_csv(DATA/'tempos_brutos.csv',sep=';')
        resumo=pd.read_csv(DATA/'resultados_foca_aluno.csv',sep=';',decimal=',')
        self.assertEqual(len(raw),1800)
        self.assertEqual(len(resumo),60)
        self.assertEqual(set(raw.imagem_id),{'imagem_01','imagem_02'})
        self.assertTrue((raw.groupby(['imagem_id','variante','n','k']).size()==30).all())
        self.assertFalse(raw.duplicated(['imagem_id','variante','n','k','repeticao']).any())
        for imagem_id,group in raw.groupby('imagem_id'):
            local=pd.read_csv(DATA/imagem_id/'tempos_brutos.csv',sep=';')
            pd.testing.assert_frame_equal(group.drop(columns=['imagem_id','imagem_fonte']).reset_index(drop=True),local)

if __name__=='__main__': unittest.main(verbosity=2)
