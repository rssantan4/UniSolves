"""Validação funcional fora do cronômetro; inclui defeitos herdados do baseline."""
import ast
import copy
import random
import sys
import unittest
from pathlib import Path
from unittest.mock import patch
import numpy as np

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from src.fcm_baseline import fcm_puro as baseline
from src.fcm_unrolling import fcm_puro as unrolling


def executar_rastreado(func, X, K, **kwargs):
    """Captura estado no teste de parada sem editar/instrumentar o fonte."""
    source = Path(func.__code__.co_filename).read_text().splitlines()
    stop = next(i + 1 for i, s in enumerate(source) if s.strip() == 'if max_diff < epsilon:')
    estados = []
    def trace(frame, event, arg):
        if frame.f_code is func.__code__ and event == 'line' and frame.f_lineno == stop:
            estados.append(copy.deepcopy({k: frame.f_locals[k] for k in ('iteracao', 'max_diff', 'C', 'U')}))
        return trace
    random.seed(42)
    previous = sys.gettrace()
    try:
        sys.settrace(trace)
        result = func(X, K, **kwargs)
    finally:
        sys.settrace(previous)
    return result, estados


class TestFCM(unittest.TestCase):
    def test_equivalencia_saidas_trajetoria_e_invariantes(self):
        rng = random.Random(17)
        casos = {
            'aleatoria_17': [[rng.uniform(0,255) for _ in range(3)] for _ in range(17)],
            'gradiente_15': [[float(i*17), float(255-i*17), float(i*8)] for i in range(15)],
            'repetidos_21': [[0.,10.,20.], [200.,180.,160.], [50.,90.,120.]]*7,
            'monocromatica_9': [[128.,128.,128.]]*9,
            'preta_7': [[0.,0.,0.]]*7,
            'impar_5': [[i*40., i*10., 120.] for i in range(5)],
        }
        for nome,X in casos.items():
            for K in (2,3,4):
                with self.subTest(caso=nome,K=K):
                    original=copy.deepcopy(X)
                    (C,U), t1=executar_rastreado(baseline,X,K)
                    (D,V), t2=executar_rastreado(unrolling,X,K)
                    self.assertEqual((C,U),(D,V)) # mesma ordem: igualdade exata observada
                    self.assertEqual(t1,t2)
                    self.assertEqual(X,original)
                    self.assertEqual(np.shape(U),(len(X),K))
                    self.assertTrue(np.isfinite(C).all() and np.isfinite(U).all())
                    self.assertTrue(((np.array(U)>=0)&(np.array(U)<=1)).all())
                    np.testing.assert_allclose(np.sum(U,axis=1),1,rtol=0,atol=1e-12)
                    self.assertTrue(t1[-1]['max_diff']<0.01 or len(t1)==100)

    def test_singularidade_tardia_herdada(self):
        # U inicial [[1,0],[.5,.5]] -> C[1] coincide com segundo pixel.
        # Para este pixel, j=0 divide por distancia[1]=0 antes de j=1.
        for func in (baseline,unrolling):
            with patch('random.random',side_effect=[1.,0.,1.,1.]):
                with self.assertRaises(ZeroDivisionError):
                    func([[0.,0.,0.],[2.,2.,2.]],2)

    def test_convergencia_singular_ignora_delta_real_herdado(self):
        for func in (baseline,unrolling):
            (_,U),trace=executar_rastreado(func,[[0.,0.,0.]]*7,3)
            self.assertEqual(len(trace),1)
            self.assertEqual(trace[-1]['max_diff'],0.)
            self.assertEqual(U,[[1.,0.,0.]]*7)
            # U inicial aleatorio nao era one-hot: delta zero nao representa delta real.

    def test_escopo_ast_exatamente_tres_lacos(self):
        self.assertEqual((ROOT/'src/fcm_baseline.py').read_bytes(),
                         (ROOT/'originais/fcm_puro_transcrito_pdf.py').read_bytes())
        tree=ast.parse((ROOT/'src/fcm_baseline.py').read_text())
        class Expandir(ast.NodeTransformer):
            count=0
            def visit_For(self,node):
                if isinstance(node.target,ast.Name) and node.target.id=='c':
                    self.count+=1
                    out=[]
                    for channel in range(3):
                        class Indice(ast.NodeTransformer):
                            def visit_Name(self,n):
                                return ast.copy_location(ast.Constant(channel),n) if n.id=='c' else n
                        out.extend(Indice().visit(copy.deepcopy(n)) for n in node.body)
                    return out
                return self.generic_visit(node)
        transform=Expandir(); expected=transform.visit(tree)
        actual=ast.parse((ROOT/'src/fcm_unrolling.py').read_text())
        self.assertEqual(transform.count,3)
        self.assertEqual(ast.dump(expected),ast.dump(actual))

    def test_equipe_mesmo_algoritmo_sem_logs(self):
        tree=ast.parse((ROOT/'originais/FCM_PURO.py').read_text())
        f=next(n for n in tree.body if isinstance(n,ast.FunctionDef))
        f.name='fcm_puro'
        class Limpar(ast.NodeTransformer):
            def visit_Expr(self,node):
                if isinstance(node.value,ast.Constant) and isinstance(node.value.value,str): return None
                if isinstance(node.value,ast.Call) and isinstance(node.value.func,ast.Name) and node.value.func.id=='print': return None
                return node
        f=Limpar().visit(f)
        b=next(n for n in ast.parse((ROOT/'src/fcm_baseline.py').read_text()).body if isinstance(n,ast.FunctionDef))
        self.assertEqual(ast.dump(f),ast.dump(Limpar().visit(b)))

if __name__=='__main__':
    unittest.main(verbosity=2)
