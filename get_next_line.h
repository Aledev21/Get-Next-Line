/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassis-p <aassis-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 23:36:00 by aassis-p          #+#    #+#             */
/*   Updated: 2024/11/12 11:39:06 by aassis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define MAX_COMMAND_LENGTH 256
# define BUFFER_SIZE 42
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
int mini_popen(const char *command);
char *my_fgets(char *buffer, int size, int fd);
char *my_itoa(int num);
void my_strcat(char *dest, const char *src);
int my_strlen(const char *str);

#endif
