/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:18:23 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/11 10:57:40 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	validate_map_structure(char **map)
{
	if (!map)
	{
		perror("Error: Map is null.\n");
		return (0);
	}
	if (!is_rectangular(map))
		return (0);
	if (has_invalid_char(map))
		return (0);
	if (!has_surrounding_walls(map))
	{
		ft_printf("Error: Map is not properly enclosed by walls.(1)\n");
		return (0);
	}
	if (!has_required_elements(map))
		return (0);
	return (1);
}

int	validate_map(char **map)
{
	int			px;
	int			py;
	t_flood		flood;

	flood.collectibles_count = 0;
	flood.found_exit = 0;
	get_player_position(map, &px, &py);
	if (!validate_map_structure(map))
		return (0);
	if (!flood_fill(map, px, py, &flood))
	{
		ft_printf("Error: Not all collectibles"
			"are reachable, or no path to exit.\n");
		return (0);
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

void	handle_map_error(t_game *game)
{
	if (game->map)
		free_map(game->map);
	if (game->map_copy)
		free_map(game->map_copy);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(1);
}
