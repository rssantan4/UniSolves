#include <unistd.h>       // Para STDIN_FD e STDOUT_FD
#include <sys/syscall.h>  // Para SYS_read e SYS_write

#define STDIN_FD  0
#define STDOUT_FD 1

int main() {
    char buffer[256];
    long len;

    // Mensagem antes da leitura
    const char *msg1 = "Digite uma string: ";
    syscall(SYS_write, STDOUT_FD, msg1, 19);   // <-- Impressão de mensagem com syscall

    // Leitura do usuário
    len = syscall(SYS_read, STDIN_FD, buffer, sizeof(buffer));  // <-- Leitura direta via syscall

    // Remove o '\n' do final, se presente
    if (len > 0 && buffer[len - 1] == '\n') {
        len--;
    }

    // Mensagem antes da exibição invertida
    const char *msg2 = "String invertida: ";
    syscall(SYS_write, STDOUT_FD, msg2, 18);   // <-- Impressão de mensagem com syscall

    // Impressão da string invertida
    for (long i = len - 1; i >= 0; i--) {
        syscall(SYS_write, STDOUT_FD, &buffer[i], 1);  // <-- Escrita caractere por caractere via syscall
    }

    // Nova linha
    char newline = '\n';
    syscall(SYS_write, STDOUT_FD, &newline, 1);        // <-- Escrita de nova linha via syscall

    return 0;
}
