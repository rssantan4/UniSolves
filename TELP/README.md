# 📊 Análise de Saúde de Repositórios Open Source

> Projeto desenvolvido para a disciplina de **Tópicos Especiais em Linguagem de Programação (TELP)** na UNEB.

## 🎯 Objetivo
Avaliar a "saúde", sustentabilidade e maturidade de repositórios do GitHub utilizando métricas quantitativas de engenharia de software (inspiradas em frameworks como **DORA** e **SPACE**). O foco foi analisar padrões de commits, envelhecimento do código e concentração de autores ("Bus Factor").

## 🛠️ Tecnologias & Ferramentas
* **Python:** Scripting e automação.
* **Pandas & Plotly:** Manipulação de dados e visualização de gráficos interativos.
* **Git Log Analysis:** Extração de metadados do histórico dos repositórios.
* **Jupyter Notebooks:** Documentação executável das análises.

## 🔍 Estudos de Caso

Foram analisados três repositórios com perfis de maturidade distintos:

### 1. [PandasAI](https://github.com/gventuri/pandas-ai) ⚠️
* **Diagnóstico:** Projeto jovem com sinais de estagnação.
* **Findings:** Alta concentração de risco (Bus Factor), onde um único autor detém cerca de **65% dos commits**, e uma queda brusca na atividade recente.

### 2. [Polars](https://github.com/pola-rs/polars) 📈
* **Diagnóstico:** Projeto em crescimento saudável e acelerado.
* **Findings:** Apresenta uma distribuição de trabalho mais equilibrada (maior autor com ~50%) e uma comunidade ativa com diversidade de arquivos sendo alterados (churn distribuído).

### 3. [PyTorch](https://github.com/pytorch/pytorch) ✅
* **Diagnóstico:** Projeto consolidado e robusto ("Healthy").
* **Findings:** Exemplo de sustentabilidade, com milhares de contribuidores, volume massivo de commits constantes e baixa dependência de indivíduos específicos (maior autor humano com apenas ~4.5% do total).

## 📂 Estrutura dos Arquivos

* `*.ipynb`: Notebooks contendo os códigos de extração de dados e plotagem dos gráficos (Histórico de commits, Pizza de autores, etc.).
* `Relatório TELP.pdf`: Documento formal com a análise detalhada, metodologia e conclusões comparativas.
* `ResumoPrimeiraProva.py`: Scripts auxiliares da disciplina.

---
*Autor: Rafael Santana*