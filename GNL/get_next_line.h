/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:18:44 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/10 11:43:02 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_strchr(const char *str, int c);
char	*strjoin_and_free(char *s1, const char *s2);
char	*extract_line(char *buffer);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*final_line(char **buffer);
char	*get_next_line(int fd);
#endif