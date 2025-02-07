/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 06:54:48 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/07 06:50:47 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	get_map_height(char **map)
{
	int	height;

	height = 0;
	while (map && map[height])
		height++;
	return (height);
}

int	is_rectangular(char **map)
{
	int	row_length;
	int	map_height;
	int	i;
	int	len;

	if (!map || !map[0])
		return (printf("Error: Map is empty.\n"), 0);
	i = 0;
	map_height = get_map_height(map);
	row_length = ft_strlen(map[0]);
	if (map[0][row_length - 1] == '\n')
		row_length--;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (map[i][len - 1] == '\n')
			len--;
		if (map_height == row_length)
		{
			printf("Error: Map is not rectangular\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_row_walls(char *row)
{
	int	row_len;
	int	j;

	if (!row)
		return (0);
	row_len = ft_strlen(row);
	if (row[row_len - 1] == '\n')
		row_len--;
	j = 0;
	while (j < row_len)
	{
		if (j == 0 || j == row_len - 1)
		{
			if (row[j] != '1')
			{
				printf("Error: Row must be all walls ('1').\n");
				return (0);
			}
		}
		j++;
	}
	return (1);
}

int	has_surrounding_walls(char **map)
{
	int	row_len;
	int	height;
	int	i;

	if (!map || !map[0])
		return (printf("Error: Map is empty.\n"), 0);
	height = get_map_height(map);
	row_len = ft_strlen(map[0]);
	if (!check_row_walls(map[0]) || !check_row_walls(map[height - 1]))
	{
		perror("Error: Top or bottom row is not surrounded by walls.\n");
		return (0);
	}
	i = 1;
	while (i < height - 1)
	{
		if (map[i][0] != '1' || map[i][row_len - 2] != '1')
		{
			perror("Error: Map must be surrounded by walls.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	get_player_position(char **map, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				*x = j;
				*y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}
