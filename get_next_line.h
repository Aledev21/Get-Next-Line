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
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

char			*get_next_line(int fd);
unsigned int	ft_strlen(char *str);
char			*ft_strdup(char *s);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strchr(char *str, char c);
char			*ft_substr(char *s, unsigned int start, unsigned int end);

#endif
