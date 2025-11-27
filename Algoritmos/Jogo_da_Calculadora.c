#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>

#define linhas 6
#define colunas 6

void regras(){
    printf("\nRegras do Jogo:\n");
    printf("1. Para jogar escolha dois números da matriz e uma operação aritmética (+, -, *, /).\n");
    printf("2. Se acertar o resultado, as posições escolhidas não estarão disponíveis.\n");
    printf("3. Não pode escolher a mesma operação consecutivamente.\n");
    printf("4. O usuário deve utilizar pelo menos 5 operações de soma e subtração, e 4 operações de multiplicação e divisão para completar o jogo.\n");
    printf("5. Após três tentativas erradas da mesma pergunta, pode pedir a resposta.\n");
    printf("6. O jogo termina quando:\n");
    printf("   a) Acertar todos os resultados em no máximo 24 tentativas.\n");
    printf("   b) Ultrapassar 24 tentativas.\n");
    printf("   c) Desejar terminar.\n");
    printf("OBS: Só podem números inteiros, ou seja, divisões não inteiras serão = 0 quando divisor > dividendo.\n");
    printf("Pressione Enter para voltar ao menu principal...");
    getchar();
    getchar();
}
/*Gera uma matriz aleatória com valores de 1 a 9*/
void gerar_matriz(int matriz[linhas][colunas]){
    int i, j;
    srand(time(NULL));
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            matriz[i][j] = (rand() % 9) + 1;
        }
    }
}
/*Imprime a matriz e a matriz de validação (1 = disponível, 0 = indisponível)*/
void imprimir_matriz(int matriz[linhas][colunas], int validar[linhas][colunas]){
    int i, j;
    printf("\nMatriz:\n");
    printf("   | 0 1 2 3 4 5\n");
    printf("---+------------\n");
    for (i = 0; i < linhas; i++) {
        printf(" %d | ", i);
        for (j = 0;j < colunas; j++) {
            if (validar[i][j]) {
                printf("%d ", matriz[i][j]);
            } else {
                printf("X ");
            }
        }
        printf("\n");
    }
}
/*Escolhe o operador e calcula o resultado da operação escolhida*/
int escolher_op(int num1, int num2, char op){
    switch (op){
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 != 0) return num1 / num2;
            else return 0;
        default:
            return 0;
    }
}
/*Imprime a quantidade de operações restantes*/
void mostrar_contop(int contagem[]){
    printf("\nOperações restantes para completar a fase inicial:\n");
    printf("+ : %d\n", 5 - contagem[0]);        
    printf("- : %d\n", 5 - contagem[1]);
    printf("* : %d\n", 4 - contagem[2]);
    printf("/ : %d\n", 4 - contagem[3]);
}
void jogo(){
    int matriz[linhas][colunas];                    // Matriz principal
    int validar[linhas][colunas];                   // Matriz de validação
    int tentativas = 0;                             // Contador de tentativas
    int parescorretos = 0;                          // Contador de pares corretos, usado para saber quando o jogo acabou
    int i, j;                                       // Variáveis auxiliares
    char ultop = '\0';                              // Operador anterior, usado para evitar operações consecutivas
    int contagemop[4] = {0, 0, 0, 0};               // Contador de operações restantes
    const int opmin_soma_subtracao = 5;             // Quantidade mínima de operações de soma e subtração
    const int opmin_mult_div = 4;                   // Quantidade mínima de operações de multiplicação e divisão

    gerar_matriz(matriz);

    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            validar[i][j] = 1;
        }
    }
    
    system("cls");
    /*Jogo*/
    while (tentativas < 24 && parescorretos < 18) {
        imprimir_matriz(matriz, validar);
        int l1, c1, l2, c2;                         // Linha e coluna 1 e 2
        char op;
        int result;                                 

        while (1){
            printf("Escolha o seu primeiro operando (ou -1 para retornar ao menu principal):\n");
            printf("Digite a sua coluna: ");
            scanf("%d", &c1);
            if(c1 == -1) return;                   // Se o usuário digitar -1, retorna ao menu principal
            printf("Digite a sua linha: ");
            scanf("%d", &l1);
            if(l1 == -1) return;

            if (l1 >= 0 && l1 < linhas && c1 >= 0 && c1 < colunas && validar[l1][c1]) {         // Verifica se a posição estiver disponível
                break;
            } else {
                printf("Posição inválida ou já utilizada. Tente novamente.\n");
            }
        }
        while (1){
            printf("Escolha o seu segundo operando (ou -1 para retornar ao menu principal):\n");
            printf("Digite a sua coluna: ");
            scanf("%d", &c2);
            if(c2 == -1) return;
            printf("Digite a sua linha: ");
            scanf("%d", &l2);
            if(l2 == -1) return;

            if ((l2 >= 0 && l2 < linhas && c2 >= 0 && c2 < colunas) && validar[l2][c2] && (l1 != l2 || c1 != c2)) {
                break;
            } else {
                printf("Posição inválida, já utilizada ou igual à primeira posição. Tente novamente.\n");
            }
        }
        while (1){
            printf("Escolha a operação (+, -, *, /) (ou 'x' para sair): ");
            mostrar_contop(contagemop);             // Imprime a quantidade de operações restantes
            scanf(" %c", &op);                      // Leitura da operação

            if(op == 'x') return;                   // Se o usuário digitar 'x', retorna ao menu principal

            if(op == '+' || op == '-' || op == '*' || op == '/'){
                if (op != ultop) {
                    int indice_op = (op == '+') ? 0 : (op == '-') ? 1 : (op == '*') ? 2 : 3;        

                    if ((op == '+' || op == '-') && contagemop[indice_op] >= opmin_soma_subtracao){
                        printf("Você já usou a operação '%c' o número mínimo de vezes. Escolha outra operação.\n", op);
                    } else if ((op == '*' || op == '/') && contagemop[indice_op] >= opmin_mult_div){
                        printf("Você já usou a operação '%c' o número mínimo de vezes. Escolha outra operação.\n", op);
                    } else {
                        contagemop[indice_op]++;
                        ultop = op;
                        break;
                    }
                } else {
                    printf("Você não pode escolher a mesma operação consecutivamente. Escolha outra operação.\n");
                }
            } else {
                printf("Operação inválida! Escolha entre +, -, *, /.\n");
            }
        }

        int num1 = matriz[l1][c1];
        int num2 = matriz[l2][c2];
        int resultesperado = escolher_op(num1, num2, op);           // Calcula o resultado esperado

        int tentativasdepares = 0;
        int correto = 0;

        while (tentativasdepares < 3) {
            printf("Qual é o resultado de %d %c %d? ", num1, op, num2);
            scanf("%d", &result);

            if (result == resultesperado) {
                printf("Correto!\n");
                validar[l1][c1] = 0;
                validar[l2][c2] = 0;
                parescorretos++;
                correto = 1;
                break;
            } else {
                tentativasdepares++;
                tentativas++;
                if (tentativas >= 24) {
                    break;
                }
                if (tentativasdepares < 3) {
                    printf("Errado! Tente novamente.\n");
                }
            }
        }
        /* Verifica se o jogador errou todas as tentativas e oferece a opção de ganhar mais 3 tentativas ou ver a resposta */
        if (!correto && tentativas < 24) {
            char escolha;
            while (1){
                printf("Você errou todas as tentativas. Quer ganhar mais 3 tentativas ou ver a resposta? (t/r): ");
                scanf(" %c", &escolha);

                if (escolha == 'r') {
                    printf("A resposta correta era %d.\n", resultesperado);
                    break;
                } else if (escolha == 't') {
                    tentativasdepares = 0;
                    tentativas += 3;
                    if (tentativas >= 24) {
                        break;
                    }
                    while (tentativasdepares < 3) {
                        printf("Qual é o resultado de %d %c %d? ", num1, op, num2);
                        scanf("%d", &result);

                        if (result == resultesperado) {
                            printf("Correto!\n");
                            validar[l1][c1] = 0;
                            validar[l2][c2] = 0;
                            parescorretos++;
                            correto = 1;
                            break;
                        } else {
                            tentativasdepares++;
                            tentativas++;
                            if (tentativas >= 24) {
                                break;
                            }
                            if (tentativasdepares < 3) {
                                printf("Errado! Tente novamente.\n");
                            }
                        }
                    }
                    if (correto || tentativas >= 24) {
                        break;
                    }
                } else {
                    printf("Opção inválida! Escolha 't' para tentar novamente ou 'r' para ver a resposta.\n");
                }
            }
        }
        /* Verifica se o jogador ultrapassou o limite de tentativas e interrompe o jogo */
        if (tentativas >= 24) {
            break;
        }
    }
    /* Verifica se o jogador completou o jogo */
    if (parescorretos == 18) {
        printf("Parabéns! Você completou o jogo.\n");
    } else {
        printf("Fim do jogo. Você usou todas as suas tentativas :(\n");
    }
}
/* Função principal */
int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");

    char name[30];
    int menu;

    printf("Por favor, insira seu nome ou como gostaria de ser chamado: ");
    fgets(name, sizeof(name), stdin);

    size_t len = strlen(name);
    if(len > 0 && name[len-1] == '\n'){
        name[len-1] = '\0';
    }
    system("cls");

    printf("Olá, %s, bem-vindo ao nosso incrível jogo da calculadora!\n", name);

    while (1){
        printf("\nMenu Principal:\n");
        printf("1. Regras\n");
        printf("2. Jogar\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &menu);

        switch (menu){
            case 1:
                regras();
                break;
            case 2:
                jogo();
                break;
            case 3:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
    return 0;
}
