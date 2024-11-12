#include <fcntl.h>    // Para open
#include <stdio.h>     // Para printf
#include <unistd.h>    // Para close
#include "get_next_line.h" // Inclui o header do get_next_line

int main(void) {
    int fd = open("text.txt", O_RDONLY);
    if (fd == -1) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line); // Libera a memória após imprimir cada linha
    }

    close(fd); // Fecha o arquivo ao final
    return 0;
}
