/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassis-p <aassis-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 05:24:24 by aassis-p          #+#    #+#             */
/*   Updated: 2024/11/12 12:33:02 by aassis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

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
        close(pipe_fd[0]); 

        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);

        execlp("sh", "sh", "-c", command, (char *) NULL);
        
        _exit(1);
    }
    
    // Processo pai
    close(pipe_fd[1]); 
    return pipe_fd[0];
}
