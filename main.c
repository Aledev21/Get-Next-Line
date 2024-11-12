#include <fcntl.h>   
#include <stdio.h>   
#include <unistd.h>    
#include "get_next_line.h" 
int main(void) {
    int fd = open("text.txt", O_RDONLY);
    if (fd == -1) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line); 
    }

    close(fd);
    return 0;
}
