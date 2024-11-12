#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 42

// Função auxiliar para calcular o comprimento de uma string
int my_strlen(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Função auxiliar para concatenar strings manualmente
void my_strcat(char *dest, const char *src) {
    int dest_len = my_strlen(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
}

// Função auxiliar para ler do arquivo
int my_fgets(char *buffer, int size, int fd) {
    int i = 0;
    char ch;
    while (i < size - 1 && read(fd, &ch, 1) > 0) {
        buffer[i++] = ch;
        if (ch == '\n')  // Quebra ao encontrar um '\n'
            break;
    }
    buffer[i] = '\0';
    if (i == 0)  // Caso nada tenha sido lido
        return 0;
    return 1;
}

char *get_next_line(int fd) {
    char *buffer = (char *)malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return NULL;

    static int last_fd = -1;  // Armazena o último descritor de arquivo (para continuar de onde parou)
    static char *static_buffer = NULL;  // Armazena dados entre as chamadas

    // Se o descritor de arquivo mudou, precisamos começar a leitura novamente
    if (fd != last_fd) {
        if (static_buffer) {
            free(static_buffer);  // Limpa o buffer estático de uma chamada anterior
            static_buffer = NULL;
        }
        last_fd = fd;
    }

    // Caso o buffer estático tenha dados ainda não processados
    if (static_buffer) {
        // Copia dados restantes para o buffer de saída
        int i = 0;
        while (static_buffer[i] != '\0' && i < BUFFER_SIZE) {
            buffer[i] = static_buffer[i];
            i++;
        }
        buffer[i] = '\0';

        // Se o buffer estático não foi completamente lido, deixa o restante para a próxima chamada
        if (static_buffer[i] != '\0') {
            static_buffer = &static_buffer[i];
        } else {
            free(static_buffer);  // Se o buffer foi completamente lido, libera
            static_buffer = NULL;
        }

        return buffer;
    }

    // Lê uma linha do arquivo e armazena no buffer estático
    if (my_fgets(buffer, BUFFER_SIZE + 1, fd) == 0) {
        free(buffer);
        return NULL;  // Retorna NULL se não houver mais nada para ler
    }

    // Armazena a linha lida no buffer estático (caso ela não seja totalmente lida no buffer)
    static_buffer = buffer;
    return buffer;
}
