/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:27:43 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/10 12:37:35 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Helper function to join two strings and free the first
char	*strjoin_and_free(char *s1, const char *s2)
{
	size_t		len1;
	size_t		len2;
	char		*new_str;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	new_str = malloc((len1 + len2 + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	if (s1)
	{
		ft_strlcpy(new_str, s1, len1 + 1);
		free(s1);
	}
	if (s2)
		ft_strlcpy(new_str + len1, s2, len2 + 1);
	return (new_str);
}

// Function to extract a line from the buffer
char	*extract_line(char *buffer)
{
	char	*newline_pos;
	char	*line;
	int		line_length;
	int		leftover_length;

	newline_pos = ft_strchr(buffer, '\n');
	if (newline_pos)
	{
		line_length = newline_pos - buffer + 1;
		line = malloc((line_length + 1) * sizeof(char));
		if (!line)
			return (NULL);
		ft_strlcpy(line, buffer, line_length + 1);
		leftover_length = ft_strlen(buffer) - line_length;
		ft_memmove(buffer, buffer + line_length, leftover_length + 1);
	}
	else
	{
		line = ft_strdup(buffer);
		*buffer = '\0';
	}
	return (line);
}

char	*final_line(char **buffer)
{
	char	*line;

	if (**buffer)
		line = extract_line(*buffer);
	else
	{
		free(*buffer);
		*buffer = NULL;
		line = NULL;
	}
	return (line);
}

char	*read_until_newline(int fd, char *buffer)
{
	char	*temp;
	char	*newline_pos;
	int		bytes_read;

	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	newline_pos = ft_strchr(buffer, '\n');
	while (newline_pos == NULL)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		temp[bytes_read] = '\0';
		buffer = strjoin_and_free(buffer, temp);
		if (!buffer)
		{
			free(temp);
			return (NULL);
		}
		newline_pos = ft_strchr(buffer, '\n');
	}
	free(temp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	buffer = read_until_newline(fd, buffer);
	if (!buffer)
		return (NULL);
	return (final_line(&buffer));
}
