#!/usr/bin/env python3
"""Demonstração funcional da Missão 4; não executa benchmark nem altera a coleta."""
import sys

sys.dont_write_bytecode = True

import argparse
import copy
import hashlib
import json
from pathlib import Path

HERE = Path(__file__).resolve().parent
PROJECT = HERE.parent
sys.path.insert(0, str(PROJECT))
sys.path.insert(0, str(PROJECT / "tests"))

try:
    import numpy as np
    from PIL import Image
    from experimentador import descobrir_imagens, preparar_rgb, visualizar
    from src.fcm_baseline import fcm_puro as baseline
    from src.fcm_unrolling import fcm_puro as unrolling
    from test_fcm import executar_rastreado
except ImportError as exc:
    raise SystemExit(
        "Dependência ou arquivo do projeto ausente: " + str(exc)
        + "\nMantenha apresentacao/ dentro do projeto e instale requirements.txt "
        "com o mesmo Python utilizado na demonstração."
    ) from exc


def executar(imagem_id, lado, k):
    fontes = descobrir_imagens(PROJECT / "minhas_imagens")
    item, source = next((item, path) for item, path in fontes if item["id"] == imagem_id)
    with Image.open(source) as original:
        imagem = original.convert("RGB").resize((lado, lado), Image.Resampling.LANCZOS)
    X = preparar_rgb(imagem)
    entrada_antes = copy.deepcopy(X)
    parametros = dict(m=2.0, max_iter=100, epsilon=0.01)

    print("EQUIPE 10 - ANTI-TEAM | MISSAO 4 - LOOP UNROLLING")
    print("Demonstração FUNCIONAL, sem cronometragem ou nova coleta estatística.")
    print(f"Fonte: {item['arquivo']} | RGB {lado} x {lado} | n={len(X)} | K={k}")
    print("Seed=42 em cada chamada; m=2; epsilon=0.01; max_iter=100.")
    print("Rastreamento externo reutilizado dos testes; os núcleos não são alterados.\n")

    # O helper existente reaplica random.seed(42) antes de cada função.
    # Ele observa o teste de parada, fora de qualquer medição de desempenho.
    (C, U), historia_b = executar_rastreado(baseline, X, k, **parametros)
    (D, V), historia_u = executar_rastreado(unrolling, X, k, **parametros)
    C_array, D_array, U_array, V_array = map(np.asarray, (C, D, U, V))
    linhas = sorted({0, 1, 2, len(X) // 2, len(X) - 1})
    delta_c = float(np.max(np.abs(C_array - D_array)))
    delta_u = float(np.max(np.abs(U_array - V_array)))
    soma_erro = float(np.max(np.abs(U_array.sum(axis=1) - 1)))
    equivalencia = dict(
        centroides_exatamente_iguais=bool(np.array_equal(C_array, D_array)),
        pertinencias_exatamente_iguais=bool(np.array_equal(U_array, V_array)),
        trajetorias_exatamente_iguais=historia_b == historia_u,
        entrada_preservada=X == entrada_antes,
        valores_finitos=bool(np.isfinite(C_array).all() and np.isfinite(U_array).all()),
        pertinencias_no_intervalo=bool(((U_array >= 0) & (U_array <= 1)).all()),
        linhas_normalizadas=bool(np.allclose(U_array.sum(axis=1), 1, rtol=0, atol=1e-12)),
    )

    for nome, centros, historia in [("FCM Puro", C, historia_b), ("Loop Unrolling", D, historia_u)]:
        print(nome)
        for j, centro in enumerate(centros):
            print(f"  C{j}: R={centro[0]:10.6f} G={centro[1]:10.6f} B={centro[2]:10.6f}")
        final = historia[-1]["max_diff"]
        print(f"  I={len(historia)} | Delta U final={final:.12f}")
        print(f"  Critério do baseline Delta U < epsilon: {final < parametros['epsilon']}\n")

    print("CONVERGÊNCIA - mesma trajetória nas duas versões")
    indices = sorted(set(range(min(3, len(historia_b)))) | set(range(max(0, len(historia_b) - 3), len(historia_b))))
    for i in indices:
        print(f"  Iteração {i + 1:2d}: Delta U={historia_b[i]['max_diff']:.12f}")
    print("\nU RESUMIDA - matriz completa comparada; cinco linhas mostradas")
    print("  pixel   " + "  ".join(f"u[{j}]".rjust(10) for j in range(k)) + "       soma")
    for i in linhas:
        print(f"  {i:5d}   " + "  ".join(f"{val:10.6f}" for val in U[i]) + f"   {sum(U[i]):.10f}")
    print(f"\nmax |C_puro - C_unrolling| = {delta_c:.3e}")
    print(f"max |U_puro - U_unrolling| = {delta_u:.3e}")
    print(f"Maior erro na soma das linhas de U = {soma_erro:.3e} (tolerância 1e-12)")
    for nome, passou in equivalencia.items():
        print(f"  {'OK' if passou else 'FALHOU'}: {nome}")
    if not all(equivalencia.values()):
        raise AssertionError("Divergência ou invariante inválida na demonstração.")

    # Reutiliza exclusivamente o adaptador visual já existente no experimentador.
    # Os arquivos ficam separados das medições, dentro de apresentacao/.
    saida = HERE / "saida_demo" / f"{imagem_id}_{lado}_k{k}"
    saida.mkdir(parents=True, exist_ok=True)
    imagem.save(saida / "entrada.png")
    for nome, centros, pertinencias in [("baseline", C, U), ("unrolling", D, V)]:
        dest = saida / nome
        dest.mkdir(exist_ok=True)
        visualizar(centros, pertinencias, (lado, lado), dest)
    resultado = dict(
        natureza="Demonstração funcional; não é benchmark ou homologação estatística",
        imagem_id=imagem_id, fonte=item["arquivo"], fonte_sha256=item["sha256"],
        lado=lado, n=len(X), k=k, seed=42, parametros=parametros,
        centroides_baseline=C, centroides_unrolling=D,
        iteracoes_baseline=len(historia_b), iteracoes_unrolling=len(historia_u),
        delta_final_baseline=historia_b[-1]["max_diff"], delta_final_unrolling=historia_u[-1]["max_diff"],
        convergiu_baseline=historia_b[-1]["max_diff"] < parametros["epsilon"],
        convergiu_unrolling=historia_u[-1]["max_diff"] < parametros["epsilon"],
        convergencia=[dict(iteracao=i + 1, delta_u=h["max_diff"]) for i, h in enumerate(historia_b)],
        pertinencia_resumida=[dict(pixel=i, valores=U[i], soma=sum(U[i])) for i in linhas],
        shape_U=list(U_array.shape), maior_diferenca_C=delta_c, maior_diferenca_U=delta_u,
        maior_erro_soma_U=soma_erro, equivalencia=equivalencia,
        sha256_U=hashlib.sha256(json.dumps(U, separators=(",", ":")).encode()).hexdigest(),
    )
    (saida / "resultado.json").write_text(json.dumps(resultado, indent=2, ensure_ascii=False) + "\n")
    print("\nResultado completo da demonstração e imagens em:")
    print(saida)
    print("Desempenho e CV devem ser defendidos pelos CSVs da coleta R=30, não por esta execução.")
    return resultado


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--imagem", choices=["imagem_01", "imagem_02"], default="imagem_01")
    parser.add_argument("--lado", type=int, choices=[16, 24, 32, 48, 64], default=32)
    parser.add_argument("--clusters", type=int, choices=[2, 3, 4], default=3)
    args = parser.parse_args()
    executar(args.imagem, args.lado, args.clusters)
