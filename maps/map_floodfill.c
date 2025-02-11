/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 09:20:21 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/11 10:54:39 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	count_checker(int *player_count, int *exit_count, int *collectible_count)
{
	if (*player_count != 1)
	{
		ft_printf("Error: There must be at least 1 player (P).\n");
		return (0);
	}
	if (*exit_count != 1)
	{
		ft_printf("Error: There must be at least 1 exit (E).\n");
		return (0);
	}
	if (*collectible_count < 1)
	{
		ft_printf("Error: There must be at least 1 collectible (C).\n");
		return (0);
	}
	return (1);
}

int	is_valid_move_table(char **map, int x, int y)
{
	if (x < 0 || y < 0 || !map[y] || !map[y][x])
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	return (1);
}

void	update_state(char **map, int x, int y, t_flood *flood)
{
	if (map[y][x] == 'C')
		flood->collectibles_count++;
	if (map[y][x] == 'E')
		flood->found_exit = 1;
	map[y][x] = 'V';
}

void	explore_neighbors(char **map, int x, int y, t_flood *flood)
{
	flood_fill(map, x + 1, y, flood);
	flood_fill(map, x - 1, y, flood);
	flood_fill(map, x, y + 1, flood);
	flood_fill(map, x, y - 1, flood);
}

int	flood_fill(char **map, int x, int y, t_flood *flood)
{
	int	total_collectibles;

	total_collectibles = count_collectibles(map);
	if (!is_valid_move_table(map, x, y))
		return (0);
	update_state(map, x, y, flood);
	explore_neighbors(map, x, y, flood);
	return (flood->collectibles_count
		== total_collectibles && flood->found_exit);
}
