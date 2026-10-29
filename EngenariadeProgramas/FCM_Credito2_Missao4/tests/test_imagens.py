"""A restrição de fontes autorizadas é verificada antes de qualquer cronômetro."""
import hashlib
import json
from pathlib import Path
import shutil
import sys
import tempfile
import unittest
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT))
from experimentador import descobrir_imagens

class TestImagens(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory()
        self.pasta=Path(self.tmp.name)
        for p in (ROOT/'minhas_imagens').iterdir():
            shutil.copy2(p,self.pasta/p.name)

    def tearDown(self):
        self.tmp.cleanup()

    def test_duas_copias_identicas_as_autorizadas(self):
        fontes=descobrir_imagens(self.pasta)
        self.assertEqual(len(fontes),2)
        self.assertEqual({p.name for _,p in fontes},{'images.jpeg','images (1).jpeg'})
        for item,path in fontes:
            self.assertEqual(hashlib.sha256(path.read_bytes()).hexdigest(),item['sha256'])

    def test_rejeita_terceira_imagem(self):
        shutil.copy2(self.pasta/'images.jpeg',self.pasta/'terceira.jpeg')
        with self.assertRaisesRegex(ValueError,'exclusivamente'):
            descobrir_imagens(self.pasta)

    def test_rejeita_substituicao_de_conteudo(self):
        (self.pasta/'images.jpeg').write_bytes(b'conteudo diferente')
        with self.assertRaisesRegex(ValueError,'diferente'):
            descobrir_imagens(self.pasta)

    def test_rejeita_fonte_faltante(self):
        (self.pasta/'images (1).jpeg').unlink()
        with self.assertRaisesRegex(ValueError,'exclusivamente'):
            descobrir_imagens(self.pasta)

if __name__=='__main__': unittest.main(verbosity=2)
