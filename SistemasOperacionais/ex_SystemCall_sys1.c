#include <unistd.h>     // Para definicoes como STDIN_FILENO
#include <sys/syscall.h> // Para constantes como SYS_read

#define STDIN_FD  0
#define STDOUT_FD 1

int main() {
    char buffer[256];
    long len;

    // syscall read: SYS_read(fd, buf, count)
    len = syscall(SYS_read, STDIN_FD, buffer, sizeof(buffer));  // <-- Leitura direta via syscall

    // Remover \n, se presente
    if (len > 0 && buffer[len - 1] == '\n') {
        len--;
    }

    // Inverter e imprimir com syscalls
    for (long i = len - 1; i >= 0; i--) {
        syscall(SYS_write, STDOUT_FD, &buffer[i], 1);           // <-- Escrita caractere por caractere via syscall
    }

    // Nova linha
    char newline = '\n';
    syscall(SYS_write, STDOUT_FD, &newline, 1);                 // <-- Escrita de nova linha via syscall

    return 0;
}
