"""Derivado das seções 4-7 do notebook original; ver criar_adaptacao.py e diff."""
import json
import numpy as np
import pandas as pd
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit


def analisar(df_raw, saida_dir, k_list):
    # ==========================================
    # 4. Pré-processamento e Validação F.O.C.A.
    # ==========================================
    if not df_raw.empty:
        df_filtered = pd.DataFrame()

        # Filtragem de Outliers (Percentis 5 e 95)
        for (n, k), group in df_raw.groupby(['n', 'k']):
            p05 = group['tempo'].quantile(0.05)
            p95 = group['tempo'].quantile(0.95)
            valid_mask = (group['tempo'] >= p05) & (group['tempo'] <= p95)
            df_filtered = pd.concat([df_filtered, group[valid_mask]])

        # Validação de Estabilidade (Média, Desvio e CV)
        resumo = df_filtered.groupby(['n', 'k']).agg(
            tempo_medio=('tempo', 'mean'),
            desvio=('tempo', 'std'),
            contagem_valida=('tempo', 'count')
        ).reset_index()

        resumo['CV'] = resumo['desvio'] / resumo['tempo_medio']
        resumo['estavel_CV_menor_15'] = resumo['CV'] < 0.15

        print("\n--- Resumo de Estabilidade ---")
        print(resumo)

        resumo['contagem_bruta'] = len(df_raw) // len(resumo)
        resumo['taxa_descarte'] = 1 - resumo['contagem_valida'] / resumo['contagem_bruta']
        resumo['status'] = np.where(resumo['estavel_CV_menor_15'], 'HOMOLOGADA', 'NAO HOMOLOGADA')
        df_filtered.to_csv(saida_dir / 'tempos_filtrados.csv', index=False, sep=';', decimal=',')
        resumo.to_csv(saida_dir / 'validacao_cv.csv', index=False, sep=';', decimal=',')

        # ==========================================
        # 5. Ajuste de Curvas
        # ==========================================
        def model_n_k(X, alpha, beta, gamma, delta):
            n, k = X
            return alpha * (n * k) + beta * n + gamma * k + delta

        def exibir_equacao_ajustada(popt, X_data, y_data):
            """
            Exibe no terminal a equação ajustada com notação científica legível,
            os coeficientes individuais e o coeficiente de determinação (R²).
            """
            alpha, beta, gamma, delta = popt

            # Cálculo do R² (Coeficiente de Determinação)
            y_pred = model_n_k(X_data, *popt)
            ss_res = np.sum((y_data - y_pred) ** 2)
            ss_tot = np.sum((y_data - np.mean(y_data)) ** 2)
            r2 = 1.0 - (ss_res / ss_tot) if ss_tot != 0 else 0.0

            print("\n" + "=" * 60)
            print("   MODELO EMPÍRICO AJUSTADO: T(n, K)")
            print("=" * 60)
            print("Formulação Geral:")
            print("  T(n, K) = α·(n·K) + β·n + γ·K + δ\n")
            print("Parâmetros Identificados:")
            print(f"  α (alpha) = {alpha:14.6e} s/(pixel·cluster)")
            print(f"  β (beta)  = {beta:14.6e} s/pixel")
            print(f"  γ (gamma) = {gamma:14.6e} s/cluster")
            print(f"  δ (delta) = {delta:14.6e} s (overhead base)")
            print("-" * 60)
            print("Equação Parametrizada:")
            print(f"  T(n, K) = ({alpha:.4e})·(n·K) + ({beta:.4e})·n + ({gamma:.4e})·K + ({delta:.4e})")
            print(f"Aderência Estatística (R²): {r2:.4f}")
            print("=" * 60 + "\n")

        X_data = np.vstack((resumo['n'], resumo['k']))
        y_data = resumo['tempo_medio']

        # O p0 pode precisar de sintonia dependendo da escala de tempo real
        popt, _ = curve_fit(model_n_k, X_data, y_data, p0=[1e-6, 1e-6, 1e-6, 0.01], maxfev=10000)
        resumo['tempo_predito'] = model_n_k(X_data, *popt)

        exibir_equacao_ajustada(popt, X_data, y_data)

        # ==========================================
        # 6. Plotagens Bidimensionais
        # ==========================================
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 5))

        # Plot A: Tempo vs n
        colors_k = ['red', 'green', 'blue', 'orange', 'purple']
        for idx, k in enumerate(k_list):
            dados_k = resumo[resumo['k'] == k]
            if not dados_k.empty:
                c = colors_k[idx % len(colors_k)]
                ax1.plot(dados_k['n'], dados_k['tempo_medio'], marker='o',
                         color=c, label=f'K={k} (Empírico)')
                ax1.plot(dados_k['n'], dados_k['tempo_predito'], linestyle='--',
                         color=c, alpha=0.6)

        ax1.set_xlabel('Número de Pixels (n)')
        ax1.set_ylabel('Tempo Médio de Execução (s)')
        ax1.set_title('Tempo vs Tamanho da Imagem')
        ax1.legend()
        ax1.grid(True, alpha=0.3)

        # Plot B: Tempo vs K
        n_processados = sorted(resumo['n'].unique())
        colors_n = plt.cm.viridis(np.linspace(0, 1, len(n_processados)))

        for idx, n_val in enumerate(n_processados):
            dados_n = resumo[resumo['n'] == n_val]
            if not dados_n.empty:
                ax2.plot(dados_n['k'], dados_n['tempo_medio'], marker='s',
                         color=colors_n[idx], label=f'n={n_val}')
                ax2.plot(dados_n['k'], dados_n['tempo_predito'], linestyle='--',
                         color=colors_n[idx], alpha=0.6)

        ax2.set_xlabel('Número de Clusters (K)')
        ax2.set_title('Tempo vs Número de Clusters')
        ax2.set_xticks(k_list)
        ax2.legend()
        ax2.grid(True, alpha=0.3)

        plt.tight_layout()
        arquivo_grafico = saida_dir / 'relatorio_complexidade.png'
        plt.savefig(arquivo_grafico, dpi=300)
        # Backend Agg: exportacao sem janela interativa.
        plt.close('all')

        # ==========================================
        # 6.5. Plotagem da Superfície 3D (Tempo vs n, k)
        # ==========================================
        fig_3d = plt.figure(figsize=(10, 8))
        ax_3d = fig_3d.add_subplot(111, projection='3d')

        # Cria uma malha contínua baseada nos limites reais dos dados
        n_linspace = np.linspace(resumo['n'].min(), resumo['n'].max(), 30)
        k_linspace = np.linspace(resumo['k'].min(), resumo['k'].max(), 30)
        N_mesh, K_mesh = np.meshgrid(n_linspace, k_linspace)

        # Aplica a equação ajustada em todos os pontos da malha
        T_mesh = model_n_k((N_mesh, K_mesh), *popt)

        # Desenha a superfície teórica translúcida
        surf = ax_3d.plot_surface(N_mesh, K_mesh, T_mesh, cmap='viridis', alpha=0.6,
                                  linewidth=0.1, antialiased=True)
        fig_3d.colorbar(surf, ax=ax_3d, shrink=0.5, aspect=10, pad=0.1, label='Tempo (s)')

        # Sobrepõe os pontos empíricos medidos
        ax_3d.scatter(resumo['n'], resumo['k'], resumo['tempo_medio'],
                      color='red', edgecolor='black', s=60, label='Pontos Empíricos', depthshade=False)

        ax_3d.set_xlabel('Tamanho da Imagem (n pixels)')
        ax_3d.set_ylabel('Número de Clusters (K)')
        ax_3d.set_zlabel('Tempo de Execução (s)')
        ax_3d.set_title('Superfície F.O.C.A: Tempo(n, K)')
        ax_3d.view_init(elev=25, azim=135)
        ax_3d.legend()

        plt.tight_layout()
        arquivo_superficie = saida_dir / 'superficie_3d_foca.png'
        fig_3d.savefig(arquivo_superficie, dpi=300)
        # Backend Agg: exportacao sem janela interativa.
        plt.close('all')

        print(f"\nPipeline concluído. Gráficos gerados e salvos em: {arquivo_grafico} e {arquivo_superficie}")

        # ==========================================
        # 7. Exportação dos Dados para Avaliação
        # ==========================================
        arquivo_csv = saida_dir / 'resultados_foca_aluno.csv'

        # Exporta os dados usando ponto e vírgula como separador e vírgula para decimais,
        # garantindo que o arquivo seja aberto corretamente no Excel em PT-BR.
        resumo.to_csv(arquivo_csv, index=False, sep=';', decimal=',')

        print(f"Tabela de avaliação exportada com sucesso para: {arquivo_csv}")

        residuos = y_data - resumo['tempo_predito']
        resumo.assign(residuo=residuos).to_csv(saida_dir / 'residuos.csv', index=False, sep=';', decimal=',')
        r2 = 1 - float(np.sum(residuos**2) / np.sum((y_data - y_data.mean())**2))
        design = np.column_stack([resumo.n*resumo.k, resumo.n, resumo.k, np.ones(len(resumo))])
        diag_design = np.column_stack([resumo.n*resumo.k**2, design])
        coef_diag, _, rank_diag, _ = np.linalg.lstsq(diag_design, y_data, rcond=None)
        diag_resid = y_data - diag_design @ coef_diag
        avisos = ['Ajuste descritivo na malha local; I varia com conteudo e K; nao extrapolar.',
                  'Nao mede diretamente I-Cache ou pipeline; nenhuma causalidade microarquitetural demonstrada.']
        if not resumo.estavel_CV_menor_15.all():
            avisos.append('Contem combinacoes NAO HOMOLOGADAS; ajuste exploratorio inclui todas as medias, sem ocultar falhas.')
        payload = dict(coeficientes=dict(zip(['alpha','beta','gamma','delta'],map(float,popt))),
                       r2=r2, posto=int(np.linalg.matrix_rank(design)), condicao=float(np.linalg.cond(design)),
                       n_min=int(resumo.n.min()), n_max=int(resumo.n.max()),
                       todas_homologadas=bool(resumo.estavel_CV_menor_15.all()), avisos=avisos,
                       diagnostico_nk2=dict(coeficientes=coef_diag.tolist(), posto=int(rank_diag),
                       r2=1-float(np.sum(diag_resid**2)/np.sum((y_data-y_data.mean())**2))))
        (saida_dir / 'ajuste.json').write_text(json.dumps(payload,indent=2,ensure_ascii=False))
        fig, ax = plt.subplots(figsize=(8,4))
        for k,g in resumo.assign(residuo=residuos).groupby('k'):
            ax.plot(g.n,g.residuo,'o-',label=f'K={k}')
        ax.axhline(0,color='black',lw=1); ax.set(xlabel='Pixels (n)',ylabel='Residuo (s)',title='Residuos do modelo oficial')
        ax.legend(); fig.tight_layout(); fig.savefig(saida_dir/'residuos.png',dpi=180); plt.close(fig)
        return resumo


    else:
        raise ValueError("Nenhuma amostra recebida para analise.")
