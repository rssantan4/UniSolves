#!/usr/bin/env python3
"""Investiga os CSVs existentes; não chama FCM, não mede e não grava resultados."""
import sys

sys.dont_write_bytecode = True

import math
from pathlib import Path

import pandas as pd

PROJECT = Path(__file__).resolve().parents[1]
DATA = PROJECT / "resultados/coleta_duas_imagens_R30"


def investigar():
    raw = pd.read_csv(DATA / "tempos_brutos.csv", sep=";")
    resumo = pd.read_csv(DATA / "resultados_foca_aluno.csv", sep=";", decimal=",")
    trajetorias = pd.read_csv(DATA / "convergencia.csv", sep=";")
    falhas = resumo[~resumo.estavel_CV_menor_15]
    print("INVESTIGAÇÃO SOMENTE DE LEITURA - MISSÃO 4")
    print(f"{len(raw)} tempos existentes; {int(resumo.estavel_CV_menor_15.sum())}/{len(resumo)} séries homologadas.")
    print("Nenhuma medição nova; critério preservado: CV < 0.15.\n")

    for row in falhas.itertuples():
        grupo = raw[(raw.imagem_id == row.imagem_id) & (raw.variante == row.variante)
                    & (raw.n == row.n) & (raw.k == row.k)].copy().sort_values("repeticao")
        p05, p95 = grupo.tempo.quantile([0.05, 0.95])
        grupo["retida"] = grupo.tempo.between(p05, p95)
        # Posição entre as 60 chamadas cronometradas deste caso (duas por repetição).
        grupo["chamada_no_caso"] = 2 * grupo.repeticao + grupo.ordem + 1
        validas = grupo[grupo.retida]
        media = float(validas.tempo.mean())
        desvio = float(validas.tempo.std(ddof=1))
        cv = desvio / media
        assert len(grupo) == 30 and len(validas) == row.contagem_valida
        for calculado, salvo in [(media, row.tempo_medio), (desvio, row.desvio), (cv, row.CV)]:
            assert math.isclose(calculado, salvo, rel_tol=1e-10, abs_tol=1e-14)
        assert bool(cv < 0.15) == bool(row.estavel_CV_menor_15)
        filtradas = pd.read_csv(DATA / row.imagem_id / row.variante / "tempos_filtrados.csv",
                                sep=";", decimal=",")
        filtradas = filtradas[(filtradas.n == row.n) & (filtradas.k == row.k)]
        assert sorted(validas.repeticao) == sorted(filtradas.repeticao)

        print(f"{row.imagem_fonte} | {row.variante} | n={row.n}, K={row.k}")
        print(f"P5={p05:.12f}s; P95={p95:.12f}s; retidas={len(validas)}/30")
        print(f"média={media:.12f}s; desvio amostral={desvio:.12f}s; CV={cv:.12f}")
        print(f"CV bruto={grupo.tempo.std(ddof=1) / grupo.tempo.mean():.12f}")
        print("Conferência com CSV salvo: OK. Situação: NÃO HOMOLOGADA.")
        print("Repetições começam em 0; ordem 0=primeira função, 1=segunda.")
        print(grupo[["repeticao", "ordem", "chamada_no_caso", "tempo", "retida"]].to_string(
            index=False, formatters={"tempo": lambda v: f"{v:.9f}"}))
        print("\nDescritivo bruto por posição na repetição (não é novo filtro):")
        print(grupo.groupby("ordem").tempo.agg(["count", "mean", "std", "min", "max"]).to_string(
            float_format=lambda v: f"{v:.9f}"))
        print("\nSeis maiores tempos brutos (apenas inspeção; nada é descartado por isto):")
        print(grupo.nlargest(6, "tempo")[["repeticao", "chamada_no_caso", "tempo", "retida"]].to_string(
            index=False, formatters={"tempo": lambda v: f"{v:.9f}"}))
        par = resumo[(resumo.imagem_id == row.imagem_id) & (resumo.n == row.n) & (resumo.k == row.k)]
        print("\nDuas séries do par:")
        print(par[["variante", "tempo_medio", "desvio", "CV", "status"]].to_string(index=False))
        traco = trajetorias[(trajetorias.imagem_id == row.imagem_id)
                            & (trajetorias.n == row.n) & (trajetorias.k == row.k)]
        print("\nConvergência da execução adicional, fora do timer (não é I por amostra):")
        print(traco[["variante", "I", "delta_final", "convergiu"]].to_string(index=False))
        print("\n" + "-" * 80 + "\n")

    print("Conclusão: o filtro oficial e os CVs salvos conferem. As duas falhas permanecem.")
    print("Picos recorrentes são evidência de instabilidade; GC/agendamento/energia não foram")
    print("registrados por chamada. A causa raiz das pausas não está confirmada.")


if __name__ == "__main__":
    investigar()
