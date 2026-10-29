"""Prepara somente o ZIP local do relatório para importar no Overleaf."""
from pathlib import Path
import zipfile

ROOT = Path(__file__).resolve().parent


if __name__ == "__main__":
    nomes = [
        "main.tex",
        "imagem_01_unrolling_relatorio_complexidade.png",
        "imagem_01_unrolling_superficie_3d_foca.png",
        "exemplo_segmentacao.png",
        "imagem_01_comparacao.png",
    ]
    arquivos = [ROOT / "relatorio" / nome for nome in nomes]
    for arquivo in arquivos:
        if not arquivo.is_file():
            raise FileNotFoundError(arquivo)
    destino = ROOT / "submissao_overleaf.zip"
    with zipfile.ZipFile(destino, "w", zipfile.ZIP_DEFLATED) as pacote:
        for arquivo in arquivos:
            pacote.write(arquivo, arquivo.name)
    with zipfile.ZipFile(destino) as pacote:
        assert pacote.testzip() is None
    print(f"{destino.name}: {len(arquivos)} arquivos; integridade conferida.")
