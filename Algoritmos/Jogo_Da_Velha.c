#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define TAM 3

char M[TAM][TAM];

void InicializarMatriz();
void ImprimirMatriz();
int ValidarJogada(int linha, int coluna);
int VerificarVencedor();
int VerificarEmpate();

int main() {
    setlocale(LC_ALL, "");

    InicializarMatriz();
    int linha, coluna, jogador = 1;
    char simbolo;

    while (1) {
        ImprimirMatriz();
        printf("\nJogador %d, digite a linha e a coluna (0-2) da sua jogada: ", jogador);
        scanf("%d %d", &linha, &coluna);

        if (ValidarJogada(linha, coluna)) {
            simbolo = (jogador == 1) ? 'X' : 'O';
            M[linha][coluna] = simbolo;

            if (VerificarVencedor()) {
                ImprimirMatriz();
                printf("\nJogador %d (%c) venceu o jogo!\n", jogador, simbolo);
                break;
            }

            if (VerificarEmpate()) {
                ImprimirMatriz();
                printf("\nO jogo terminou em empate!\n");
                break;
            }

            jogador = (jogador == 1) ? 2 : 1;
        } else {
            printf("\nJogada inválida! Tente novamente.\n");
        }
    }

    return 0;
}

void InicializarMatriz() {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            M[i][j] = ' ';
        }
    }
}

void ImprimirMatriz() {
    printf("\n  0 1 2\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM; j++) {
            printf("%c", M[i][j]);
            if (j < TAM - 1) printf("|");
        }
        printf("\n");
        if (i < TAM - 1) printf("  -----\n");
    }
}

int ValidarJogada(int linha, int coluna) {
    if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM && M[linha][coluna] == ' ') {
        return 1;
    }
    return 0;
}

int VerificarVencedor() {
    // Verificar linhas e colunas
    for (int i = 0; i < TAM; i++) {
        if (M[i][0] == M[i][1] && M[i][1] == M[i][2] && M[i][0] != ' ') {
            return 1;
        }
        if (M[0][i] == M[1][i] && M[1][i] == M[2][i] && M[0][i] != ' ') {
            return 1;
        }
    }

    // Verificar diagonais
    if (M[0][0] == M[1][1] && M[1][1] == M[2][2] && M[0][0] != ' ') {
        return 1;
    }
    if (M[0][2] == M[1][1] && M[1][1] == M[2][0] && M[0][2] != ' ') {
        return 1;
    }

    return 0;
}

int VerificarEmpate() {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (M[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}
