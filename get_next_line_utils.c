/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassis-p <aassis-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 05:24:24 by aassis-p          #+#    #+#             */
/*   Updated: 2024/11/12 11:41:55 by aassis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// Função auxiliar para abrir um pipe e simular popen
int mini_popen(const char *command) {
    int pipe_fd[2];
    
    // Cria o pipe
    if (pipe(pipe_fd) == -1) {
        return -1;
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return -1;
    } else if (pid == 0) { 
        // Processo filho
        close(pipe_fd[0]); // Fecha o descritor de leitura no processo filho

        // Redireciona stdout para o descritor de escrita do pipe
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);

        // Executa o comando com execlp, substituindo o processo
        execlp("sh", "sh", "-c", command, (char *) NULL);
        
        // Caso execlp falhe, encerra o processo filho
        _exit(1);
    }
    
    // Processo pai
    close(pipe_fd[1]); // Fecha o descritor de escrita no processo pai
    return pipe_fd[0]; // Retorna o descritor de leitura
}
