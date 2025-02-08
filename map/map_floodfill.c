/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 09:20:21 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/08 09:21:32 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	count_checker(int *player_count, int *exit_count, int *collectible_count)
{
	if (*player_count != 1)
	{
		perror("Error: There must be exactly 1 player (P).\n");
		return (0);
	}
	if (*exit_count != 1)
	{
		perror("Error: There must be exactly 1 exit (E).\n");
		return (0);
	}
	if (*collectible_count < 1)
	{
		perror("Error: There must be at least 1 collectible (C).\n");
		return (0);
	}
	return (1);
}

int	flood_fill(char **map, int x, int y, int *collectibles_count, int total_collectibles, int *found_exit)
{
	if (x < 0 || y < 0 || !map[y] || !map[y][x])
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	if (map[y][x] == 'E')
	{
		*found_exit = 1;
		return (0);
	}
	if (map[y][x] == 'C')
		(*collectibles_count)++;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, collectibles_count,
		total_collectibles, found_exit);
	flood_fill(map, x - 1, y, collectibles_count,
		total_collectibles, found_exit);
	flood_fill(map, x, y + 1, collectibles_count,
		total_collectibles, found_exit);
	flood_fill(map, x, y - 1, collectibles_count,
		total_collectibles, found_exit);
	return (*collectibles_count == total_collectibles && *found_exit);
}
