#include "get_next_line.h"

int my_strlen(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void my_strcat(char *dest, const char *src) {
    int dest_len = my_strlen(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
}

int my_fgets(char *buffer, int size, int fd) {
    int i = 0;
    char ch;
    while (i < size - 1 && read(fd, &ch, 1) > 0) {
        buffer[i++] = ch;
        if (ch == '\n')  
            break;
    }
    buffer[i] = '\0';
    if (i == 0) 
        return 0;
    return 1;
}

char *get_next_line(int fd) {
    char *buffer = (char *)malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return NULL;

    static int last_fd = -1;
    static char *static_buffer = NULL; 


    if (fd != last_fd) {
        if (static_buffer) {
            free(static_buffer); 
            static_buffer = NULL;
        }
        last_fd = fd;
    }
    if (static_buffer) {
        
        int i = 0;
        while (static_buffer[i] != '\0' && i < BUFFER_SIZE) {
            buffer[i] = static_buffer[i];
            i++;
        }
        buffer[i] = '\0';

        
        if (static_buffer[i] != '\0') {
            static_buffer = &static_buffer[i];
        } else {
            free(static_buffer); 
            static_buffer = NULL;
        }

        return buffer;
    }

    
    if (my_fgets(buffer, BUFFER_SIZE + 1, fd) == 0) {
        free(buffer);
        return NULL;
    }

    static_buffer = buffer;
    return buffer;
}
