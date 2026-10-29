# Crédito 2 — Equipe 10, Anti-team

**Missão 4 — Loop Unrolling:** substituir somente os três pequenos laços RGB por operações nos canais 0, 1 e 2. O baseline do professor e os demais laços estão preservados. Correspondente da auditoria cruzada: **Equipe 2 — Pixely**.

Repositório: [rssantan4/UniSolves — FCM Crédito 2](https://github.com/rssantan4/UniSolves/tree/main/EngenariadeProgramas/FCM_Credito2_Missao4).

## Arquivos principais

- **[Relatório](relatorio/main.pdf)** e [LaTeX editável](relatorio/main.tex): seis seções do template, fundamentação didática, quatro figuras e quatro tabelas.
- **[Notebook FCM Puro](experimentador_EP_2026_2_FCM_PURO.ipynb)**: experimento local com três fontes, salvo com saídas reais.
- **[Baseline](src/fcm_baseline.py)**, [variante](src/fcm_unrolling.py) e [diff da Missão 4](documentacao/diff_baseline_variante.patch): as três alterações RGB.

## Resultados e pendências

| Experimento | Dados | Situação |
|---|---|---|
| FCM Puro no notebook | 3 fontes, 1.350 medições | **45/45 séries com CV < 0,15** |
| Comparação Puro × Unrolling | 2 fontes, 1.800 medições | **58/60 séries com CV < 0,15**; duas pendentes |
| Testes funcionais, de escopo e dos dados | 12 testes | Aprovados |

As coletas usam preparos de memória diferentes. A aprovação do notebook não homologa a comparação da Missão 4. Na comparação, falharam I1/baseline e I2/Unrolling, ambos em n=2304/K=2, com CVs 0,167324 e 0,224842. Nos 28 pares homologados, a redução das médias variou de 8,39% a 12,77%.

Ainda faltam: homologar essas duas séries por nova coleta válida, realizar a auditoria com a Pixely e conferir o PDF no Overleaf. Não houve nova medição nesta revisão editorial.

## Preparar e executar

Na pasta do projeto, com Python 3.14 (a coleta usou 3.14.7):

```bash
python3 -m venv .venv
source .venv/bin/activate
python -m pip install -r requirements.txt
python -m unittest discover -s tests -v
sh apresentacao/executar_demo.sh
sh apresentacao/executar_demo.sh --cv
```

No VS Code, abra o notebook e selecione o kernel dessa `.venv`. Nesta máquina, também existe o ambiente `../.venv/bin/python`. Para mostrar a execução registrada, navegue pelas saídas salvas. Para coletar novamente, reinicie o kernel e use **Executar Tudo**; cada execução cria outra pasta, e a aprovação do CV precisa ser conferida novamente.

O notebook usa `minhas_imagens_fcm_puro/`: `images.jpeg`, `images (1).jpeg` e `images (2).jpeg`. O comparador usa `minhas_imagens/`, com as duas fontes da coleta da Missão 4. A terceira fonte ainda não foi medida com Unrolling.

Parâmetros: lados 16/24/32/48/64, K=2/3/4, R=30, seed=42, m=2, epsilon=0,01 e máximo de 100 iterações. O timer cobre o FCM completo. Conversão RGB, seed, aquecimento, exportação e visualização ficam fora da medição. O filtro P5–P95 é inclusivo; o desvio é amostral; a aprovação exige CV estritamente menor que 0,15, por fonte/versão/n/K.

A demonstração funcional não mede desempenho. Ela mostra C, U, convergência e equivalência, e grava segmentações em `apresentacao/saida_demo/`. O comando `--cv` somente lê e confere as duas reprovações existentes.

Para uma nova comparação, usar uma pasta de saída nova:

```bash
python experimentador.py --saida resultados/nova_comparacao
```

## Dados publicados

- [Comparação da Missão 4](resultados/coleta_duas_imagens_R30/): tempos brutos e filtrados, tabelas, convergência, comparação, gráficos e metadados.
- [Notebook Puro](resultados/fcm_puro_notebook/coleta_20261027_083247_010287/): 1.350 tempos, tabelas de CV, gráficos 2D/3D, ajustes e ambiente.

Os JSONs de imagens autorizadas, protocolo, ambiente, ajustes e homologação são parte da reprodução. Os CSVs permitem conferir os números do relatório. Novas tentativas de coleta ficam locais até serem revisadas e incluídas no versionamento.

O modelo `αnK + βn + γK + δ` é o ajuste pedido no template. Ele não prova O(nK): o núcleo mantém custo O(I·n·K²). As limitações herdadas em distâncias nulas permanecem nas duas versões.

## Relatório e GitHub

O repositório contém código, testes, imagens de entrada, notebook integrado, dados das duas coletas, figuras principais, LaTeX e PDF. O README é o guia público único. Materiais originais de referência, guias locais repetidos, auditorias de manutenção, dumps, logs, caches e visualizações auxiliares são ignorados pelo Git.

As duas cópias Python em `originais/` são mantidas porque os testes verificam a fidelidade ao baseline. Os PDFs e o notebook K-Means recebidos do professor permanecem como referências locais, sem serem dependências da execução integrada.

Para preparar o Overleaf, executar `python empacotar.py`. Importar o `submissao_overleaf.zip` gerado, selecionar `main.tex` e compilar. O ZIP é local; o PDF, o LaTeX e suas quatro figuras são versionados. Depois de editar o relatório, gerar novamente o pacote.

## Submissão no Teams

O anexo obrigatório é `relatorio/main.pdf`, compilado do template oficial. Ele contém fundamentação da Missão 4, snippet, gráficos 2D/3D, tabelas e o link do repositório. O enunciado não exige anexar a pasta inteira nem um ZIP do código. Se quiser fornecer também o LaTeX editável, use `submissao_overleaf.zip`, gerado por `python empacotar.py`.

O PDF apresenta os dados reais e informa as duas séries da comparação que ainda não atingiram CV < 0,15; sua existência impede declarar homologação integral da bancada da Missão 4.
