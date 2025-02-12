/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 09:16:14 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/12 12:42:01 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	open_file(const char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		perror("Error opening map file");
	return (fd);
}

char	**allocate_map(int line_count)
{
	char	**map;

	map = malloc(sizeof(char *) * (line_count + 1));
	if (!map)
		perror("Error: Memory allocation failed");
	return (map);
}

int	count_lines(const char *file_path)
{
	int		fd;
	int		count;
	char	*line;

	fd = open_file(file_path);
	if (fd < 0)
		return (-1);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\0')
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

void	free_map_memory(char **map, int size)
{
	while (size > 0)
		free(map[--size]);
	free(map);
}

void	read_lines(int fd, char **map)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\0')
			map[i++] = line;
		else
			free(line);
		line = get_next_line(fd);
	}
	map[i] = NULL;
}
