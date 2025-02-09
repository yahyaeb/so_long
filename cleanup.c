/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:18:39 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/09 13:06:44 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	close_window_x(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	cleanup_game(game);
	exit(0);
}

void	destroy_param(t_game *game)
{
	if (game->textures.floor)
		mlx_destroy_image(game->mlx, game->textures.floor);
	if (game->textures.wall)
		mlx_destroy_image(game->mlx, game->textures.wall);
	if (game->textures.player)
		mlx_destroy_image(game->mlx, game->textures.player);
	if (game->textures.collectible)
		mlx_destroy_image(game->mlx, game->textures.collectible);
	if (game->textures.exit)
		mlx_destroy_image(game->mlx, game->textures.exit);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return;

	// ✅ Use free_map() instead of manually freeing maps
	free_map(game->map_copy);
	free_map(game->map);

	destroy_param(game);

	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

