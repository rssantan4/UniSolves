#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#define BUFFER_SIZE 1024

// Verifica se a string representa um número (PID)
int is_number(const char *str) {
    while (*str) {
        if (!isdigit(*str++)) return 0;
    }
    return 1;
}

// Mostra informações de um processo
void mostrar_info_processo(const char *pid) {
    char path[BUFFER_SIZE], linha[BUFFER_SIZE];
    FILE *arquivo;
    char nome[BUFFER_SIZE] = "Desconhecido";
    long memoria_kb = 0;

    // Nome do processo
    snprintf(path, sizeof(path), "/proc/%s/status", pid);
    arquivo = fopen(path, "r");
    if (arquivo) {
        while (fgets(linha, sizeof(linha), arquivo)) {
            if (strncmp(linha, "Name:", 5) == 0) {
                sscanf(linha, "Name:\t%1023s", nome);
            } else if (strncmp(linha, "VmRSS:", 6) == 0) {
                sscanf(linha, "VmRSS:\t%ld", &memoria_kb);
            }
        }
        fclose(arquivo);
    }

    printf("%-10s %-30s %10ld KB\n", pid, nome, memoria_kb);
}

// Lista os processos
void listar_processos() {
    DIR *dir = opendir("/proc");
    struct dirent *ent;

    if (!dir) {
        perror("Não foi possível abrir /proc");
        return;
    }

    printf("%-10s %-30s %10s\n", "PID", "Nome", "Memória");
    printf("-------------------------------------------------------------\n");

    while ((ent = readdir(dir)) != NULL) {
        if (is_number(ent->d_name)) {
            mostrar_info_processo(ent->d_name);
        }
    }

    closedir(dir);
}

// Encerra processo pelo PID
void encerrar_processo(pid_t pid) {
    if (kill(pid, SIGTERM) == 0) {
        printf("Processo %d encerrado com sucesso.\n", pid);
    } else {
        perror("Erro ao encerrar o processo");
    }
}

int main() {
    int opcao;
    pid_t pid;
    int processos_listados = 0;

    while (1) {
        printf("\n--- Monitor de Processos ---\n");
        printf("1. Listar processos\n");
        if (processos_listados) {
            printf("2. Encerrar processo (por PID)\n");
        }
        printf("3. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listar_processos();
                processos_listados = 1;
                break;
            case 2:
                if (processos_listados) {
                    printf("Digite o PID do processo a encerrar: ");
                    scanf("%d", &pid);
                    encerrar_processo(pid);
                } else {
                    printf("Você precisa listar os processos antes de encerrar um!\n");
                }
                break;
            case 3:
                exit(0);
            default:
                printf("Opção inválida!\n");
        }
    }

    return 0;
}
