#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>



/* Estrutura de dados para armazenar os ususarios */
typedef struct Users{
    char nickname[20];
    int score;
}Users;

/* Adiciona um novo usuário ao array dinâmico*/
void add_userInArray(Users **users, int *size, char *nickname, int score){
    
    
    // se o array estiver vazio cria o primeiro elemento
    if(*size  == 0){
        *users = malloc(sizeof(Users));
        if(*users == NULL){
            printf("Erro ao alocar memoria\n");
            exit(1);
        }
        strcpy((*users)[0].nickname, nickname);
        (*users)[0].score = score;
        *size = 1;
    }else{
        *users = realloc(*users, (*size + 1) * sizeof(Users));
        if(*users == NULL){
            printf("Erro ao alocar memoria\n");
            exit(1);
        }

        strcpy((*users)[*size].nickname, nickname);
        (*users)[*size].score = score; 
        *size = *size + 1; // (*size)++;

    }
}

/* Le os dados de um arquivo e armazena no array dinâmico*/
void read_file(Users **users, int *size, char *filename){

    FILE *file = fopen(filename, "r");

    if(file == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    char nickname[20];
    int score;

    while(fgets(nickname, sizeof(nickname), file) != NULL){
        char auxScore[5];
        fgets(auxScore, sizeof(auxScore), file);

        // retira o '\n' do final da linha
        strtok(auxScore, "\n");
        strtok(nickname, "\n");

        score = atoi(auxScore);

        
        add_userInArray(users, size, nickname, score);
    }
    fclose(file);
}
/* Escreve os dados de um array dinâmico em um arquivo*/
void write_file(Users *users, int size, char *filename){

    FILE *file = fopen(filename, "w");

    if(file == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    for(int i = 0; i < size; i++){
        fprintf(file, "%s\n%d\n", users[i].nickname, users[i].score);
    }
    fclose(file);
}

void show_ranking(Users *users, int size) {
    printf("\n=== Pontuação de Jogadores ===\n");
    for (int i = 0; i < size; i++) {
        printf("%d. %s - %d pontos\n", i + 1, users[i].nickname, users[i].score);
    }
    printf("===========================\n");
}

// jogo
#define MAX_TAM 5

char **M; // Ponteiro para matriz dinâmica
int TAM;  // Tamanho da matriz

void regras();
void InicializarMatriz();
void ImprimirMatriz();
int ValidarJogada(int linha, int coluna);
int VerificarVencedor();
int VerificarEmpate();
int VerificarTrinca(int jogador);
void LiberarMatriz();
void regras();
void jogo(const char *name1, const char *name2,  int *score1, int *score2);

int main() {
    setlocale(LC_ALL, "");
    srand(time(NULL));

    Users *users = NULL;                        //ponteiro para armazenar dinamicamente os usuários
    int size = 0;                               //armazena o tamanho do array dinâmico de usuários
    read_file(&users, &size, "users.txt");      //lê os dados dos jogadores de um arquivo e os armazena no array dinâmico
    char name1[30];
    int posi[2];                                //indices dos jogadores logados no array de usuários
    int score1 = 0;
    char name2[30];
    int score2 = 0;                             //pontuação dos players logados

    while (true) {
        printf("\nEscolha uma opção:\n");
        printf("1 - Cadastrar jogador\n");
        printf("2 - Login\n");
        printf("3 - Mostrar Pontuações\n");
        printf("4 - Sair\n");

        int opcaorank;
        bool next = false;
        scanf(" %d", &opcaorank);
        while (getchar() != '\n');

        switch (opcaorank) {
            case 1: {
                printf("Por favor, insira o nome do jogador: ");
                char nickname[20];
                fgets(nickname, sizeof(nickname), stdin);
                strtok(nickname, "\n");

                if (size > 0 && strcmp(users[size - 1].nickname, nickname) == 0) {
                    printf("Jogador já cadastrado.\n");
                } else {
                    add_userInArray(&users, &size, nickname, 0);
                    write_file(users, size, "users.txt");
                    printf("Jogador cadastrado com sucesso!\n");
                }
                break;
            }
            case 2: {
               for(int i = 0; i < 2; i++){
                    printf("Por favor, insira o nome do jogador %i: ",i +1);
                    char nickname[20];
                    fgets(nickname, sizeof(nickname), stdin);
                    strtok(nickname, "\n");

                    
                    bool found = false;
                    for (int j = 0; j < size; j++) {
                        if (strcmp(users[j].nickname, nickname) == 0) {
                            posi[i] = j;
                            found = true;
                            break;
                        }
                    }
                    if (found) {
                        if(i == 0){
                            strcpy(name1, nickname);
                            score1 = users[posi[i]].score;
                        } else if(i == 1){
                            strcpy(name2, nickname);
                            score2 = users[posi[i]].score;
                            printf("\nscore jogador 1: %d\n", score1);
                            printf("\nscore jogador 2: %d\n", score2);
                            
                        }
                        next = true;
                        printf("Login para o jogador %i realizado com sucesso!\n", i + 1);

                    } else {
                        next = false;
                        printf("Jogador não cadastrado.\n");
                        break;
                    }
                    
               }
               break;
            }
            case 3:
                show_ranking(users, size);
                break;
            case 4:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opção inválida!\n");
        }

        if (next) break;
    }

    
    size_t len2 = strlen(name2);
    if(len2 > 0 && name2[len2-1] == '\n'){
        name2[len2-1] = '\0';
    }

    ///
    #ifdef _WIN32
        system("cls"); 
    #else
        system("clear"); 
    #endif

    int opcao;
    do {
        printf("=== Menu ===\n");
        printf("1 - Jogar\n");
        printf("2 - Regras\n");
        printf("3 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer

        switch (opcao) {
            case 1:
                jogo(name1, name2, &score1, &score2);

                users[posi[0]].score = score1;
                users[posi[1]].score = score2;
                write_file(users, size, "users.txt");
                break;
            case 2:
                regras();
                break;
            case 3:
                printf("Saindo do jogo. Ate a proxima!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 3);

    return 0;
}
/* Função principal do jogo */
void jogo(const char *name1, const char *name2, int *score1, int *score2) {
    TAM = (rand() % 2 == 0) ? 3 : 5;

    M = (char **)malloc(TAM * sizeof(char *));
    for (int i = 0; i < TAM; i++) {
        M[i] = (char *)malloc(TAM * sizeof(char));
    }

    InicializarMatriz();

    // Declaração de variáveis usadas durante o jogo
    int linha, coluna, jogador = 1, bloqueioPoderTrinca = 0;
    char simbolo;
    
    while (1) {
        ImprimirMatriz();
        printf("\n%s, digite a linha e a coluna (0-%d) da sua jogada: ", (jogador == 1) ? name1 : name2, TAM - 1);
        scanf("%d %d", &linha, &coluna);

        if (ValidarJogada(linha, coluna)) {
            simbolo = (jogador == 1) ? 'X' : 'O'; // define o simbolo de acordo com o jogador atual, alternando entre si
            M[linha][coluna] = simbolo;

            // Verificar condição de vitória
            if (VerificarVencedor()) {
                ImprimirMatriz();

            // Atualiza o placar do jogador vencedor
                printf("\n%s (%c) venceu o jogo!\n", (jogador == 1) ? name1 : name2, simbolo);
                if (jogador == 1) {
                *score1 = *score1 + 1;
            } else {
                *score2 = *score2 + 1;
            }
            
                printf("\nScore %s: %d\n", name1, *score1);
                printf("Score %s: %d\n", name2, *score2);
                
                break;
            }

            // Verificar trinca somente na matriz 5x5
            if (TAM == 5 && bloqueioPoderTrinca == 0 && VerificarTrinca(jogador)) {
                int opcao;
                printf("\n%s, você conseguiu uma trinca!\n", (jogador == 1) ? name1 : name2);
                printf("Escolha seu poder: \n");
                printf("1 - Sobrescrever um símbolo adversário.\n");
                printf("2 - Realizar uma jogada adicional.\n");
                scanf("%d", &opcao);

                if (opcao == 1) {
                    printf("\nDigite a linha e a coluna do símbolo a ser sobrescrito: ");
                    scanf("%d %d", &linha, &coluna);
                    if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM && M[linha][coluna] != simbolo && M[linha][coluna] != ' ') {
                        M[linha][coluna] = simbolo;
                        printf("Símbolo sobrescrito com sucesso!\n");
                    } else {
                        printf("Posição inválida para sobrescrição. Poder perdido.\n");
                    }
                } else if (opcao == 2) {
                    printf("Você ganhou uma jogada adicional! Realize sua jogada.\n");
                    bloqueioPoderTrinca = 1; // Bloqueia o ganho do poder na próxima jogada
                    continue; // pula a troca de jogador para que o jogador possa realizar a jogada adicional
                }
                bloqueioPoderTrinca = 1; // Bloqueia o ganho do poder na próxima jogada
            }

            // Verificar empate
            if (VerificarEmpate()) {
                ImprimirMatriz();
                printf("\nO jogo terminou em empate!\n");
                break;
            }

            // Alterna o jogador (1 para 2, ou 2 para 1)
            jogador = (jogador == 1) ? 2 : 1;
            bloqueioPoderTrinca = 0; // Desbloqueia o ganho do poder para o próximo jogador
        } else {
            printf("\nJogada inválida! Tente novamente.\n");
        }
    }

    LiberarMatriz();
}

void InicializarMatriz() {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            M[i][j] = ' ';
        }
    }
}

void ImprimirMatriz() {
    printf("\n  ");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM; j++) {
            printf("%c", M[i][j]);
            if (j < TAM - 1) printf("|");
        }
        printf("\n");
        if (i < TAM - 1) {
            printf("  ");
            for (int k = 0; k < (TAM * 2 - 1); k++) {
                printf("-");
            }
            printf("\n");
        }
    }
}

// Verifica se a posição escolhida está dentro dos limites e se está vazia.
int ValidarJogada(int linha, int coluna) {
    if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM && M[linha][coluna] == ' ') {
        return 1;
    }
    return 0;
}

int VerificarVencedor() {
    // Verificar linhas e colunas
    for (int i = 0; i < TAM; i++) {
        int linhaIgual = 1, colunaIgual = 1;
        for (int j = 1; j < TAM; j++) {
            if (M[i][j] != M[i][0] || M[i][0] == ' ') linhaIgual = 0;
            if (M[j][i] != M[0][i] || M[0][i] == ' ') colunaIgual = 0;
        }
        if (linhaIgual || colunaIgual) return 1;
    }

    // Verificar diagonais
    int diag1 = 1, diag2 = 1;
    for (int i = 1; i < TAM; i++) {
        if (M[i][i] != M[0][0] || M[0][0] == ' ') diag1 = 0;
        if (M[i][TAM - i - 1] != M[0][TAM - 1] || M[0][TAM - 1] == ' ') diag2 = 0;
    }
    if (diag1 || diag2) return 1;

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

int VerificarTrinca(int jogador) {
    char simbolo = (jogador == 1) ? 'X' : 'O';

    // Verificar trinca em linhas
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j <= TAM - 3; j++) {
            if (M[i][j] == simbolo && M[i][j + 1] == simbolo && M[i][j + 2] == simbolo) {
                return 1;
            }
        }
    }

    // Verificar trinca em colunas
    for (int j = 0; j < TAM; j++) {
        for (int i = 0; i <= TAM - 3; i++) {
            if (M[i][j] == simbolo && M[i + 1][j] == simbolo && M[i + 2][j] == simbolo) {
                return 1;
            }
        }
    }

    // Verificar trinca em diagonais (principal)
    for (int i = 0; i <= TAM - 3; i++) {
        for (int j = 0; j <= TAM - 3; j++) {
            if (M[i][j] == simbolo && M[i + 1][j + 1] == simbolo && M[i + 2][j + 2] == simbolo) {
                return 1;
            }
        }
    }

    // Verificar trinca em diagonais (secundária)
    for (int i = 0; i <= TAM - 3; i++) {
        for (int j = 2; j < TAM; j++) {
            if (M[i][j] == simbolo && M[i + 1][j - 1] == simbolo && M[i + 2][j - 2] == simbolo) {
                return 1;
            }
        }
    }

    return 0;
}

void LiberarMatriz() {
    for (int i = 0; i < TAM; i++) {
        free(M[i]);
    }
    free(M);
}

void regras() {
    #ifdef _WIN32
        system("cls"); // Para Windows
    #else
        system("clear"); // Para Linux
    #endif
    printf("=== Regras do Jogo da Velha ===\n\n");
    printf("1. O tabuleiro pode ser 3x3 ou 5x5.\n");
    printf("2. O jogo termina quando:\n");
    printf("   - Na matriz 3x3: um jogador completa três símbolos iguais na horizontal, vertical ou diagonal.\n");
    printf("   - Na matriz 5x5: um jogador completa cinco símbolos iguais na horizontal, vertical ou diagonal.\n");
    printf("3. Jogadores alternam símbolos: 'X' e 'O'.\n");
    printf("4. Ao formar uma trinca ( X X X ), em qualquer direção, no modo 5x5, o jogador pode:\n");
    printf("   - [1] Sobrescrever um símbolo do oponente.\n");
    printf("   - [2] Fazer uma jogada extra.\n");
    printf("   - Um jogador não pode ganhar o poder duas vezes consecutivas.\n");
    printf("5. O jogo termina em empate se o tabuleiro estiver cheio e ninguém vencer.\n\n");
    printf("Agora que já entederam as regras pressione Enter para realmente começarem a jogar :)\n");
    getchar();
    getchar();
}
