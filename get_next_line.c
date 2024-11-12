/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassis-p <aassis-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 23:34:15 by aassis-p          #+#    #+#             */
/*   Updated: 2024/11/12 12:33:12 by aassis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char *my_itoa(int num) {
	int len = 0;
	int temp = num;

	do {
		len++;
		temp /= 10;
	} while (temp);

	char *str = (char *)malloc(len + 1);
	if (!str) return NULL;

	str[len] = '\0';
	while (len--) {
		str[len] = '0' + (num % 10);
		num /= 10;
	}
	return str;
}

// Função auxiliar para simular fgets usando read
char *my_fgets(char *buffer, int size, int fd) {
	int i = 0;
	char ch;
	while (i < size - 1 && read(fd, &ch, 1) > 0) {
		buffer[i++] = ch;
		if (ch == '\n')
			break;
	}
	buffer[i] = '\0';
	if (i == 0)  // Caso nada tenha sido lido
		return NULL;
	return buffer;
}

char *get_next_line(int fd) {
	char *buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return NULL;
		
	static int pipe_fd = -1;
	if (pipe_fd == -1)
	{
		char command[MAX_COMMAND_LENGTH] = "sed -n p <&";
		
		char *fd_str = my_itoa(fd);
		if (!fd_str) {
			free(buffer);
			return NULL;
		}
		my_strcat(command, fd_str); // Concatena o `fd_str` ao comando
		free(fd_str);

		pipe_fd = mini_popen(command);
		if (pipe_fd == -1) {
			free(buffer);
			return NULL;
		}
	}
	if (my_fgets(buffer, BUFFER_SIZE + 1, pipe_fd) == NULL) {
		free(buffer);
		buffer = NULL;
		close(pipe_fd);
		pipe_fd = -1;
	}

	return buffer;
}
