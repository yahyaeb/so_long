/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 06:54:48 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/10 13:02:23 by yel-bouk         ###   ########.fr       */
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
	int	i;
	int	len;

	if (!map || !map[0])
		return (ft_printf("Error: Map is empty.\n"), 0);
	row_length = ft_strlen(map[0]);
	if (map[0][row_length - 1] == '\n')
		row_length--;
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (map[i][len - 1] == '\n')
			len--;
		if (len != row_length)
		{
			ft_printf("Error: Map is not rectangular\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_row_walls(char *row)
{
	int	row_len;

	if (!row)
		return (0);
	row_len = ft_strlen(row);
	if (row[row_len - 1] == '\n')
		row_len--;
	if (row[0] != '1' || row[row_len - 1] != '1')
		return (0);
	return (1);
}

int	check_top_bottom_walls(char *line)
{
	int	row_len;
	int	i;

	i = 0;
	if (!line)
		return (0);
	row_len = ft_strlen(line) - 1;
	while (i < row_len)
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	has_surrounding_walls(char **map)
{
	int	height;
	int	i;

	if (!map || !map[0])
		return (ft_printf("Error: Map is empty.\n"), 0);
	height = get_map_height(map);
	if (!check_top_bottom_walls(map[0])
		|| !check_top_bottom_walls(map[height - 1]))
		return (0);
	i = 0;
	while (i < height)
	{
		if (!check_row_walls(map[i]))
			return (0);
		i++;
	}
	return (1);
}
