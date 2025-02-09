/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 06:42:53 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/08 11:50:23 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_player_pos(t_game *game)
{
	int	i;
	int	k;

	i = 0;
	while (game->map[i])
	{
		k = 0;
		while (game->map[i][k])
		{
			if (game->map[i][k] == 'P')
			{
				game->player_x = k;
				game->player_y = i;
				return ;
			}
			k++;
		}
		i++;
	}
}

void	create_window(t_game *game)
{
	int	window_width;
	int	window_height;

	window_width = (strlen(game->map[0]) - 1) * TILE_SIZE;
	window_height = get_map_height(game->map) * TILE_SIZE;
	game->win = mlx_new_window(game->mlx, window_width,
			window_height, "So Long");
	if (!game->win)
	{
		perror("Error: Failed to create window");
		cleanup_game(game);
		exit(1);
	}
}

void	initialize_game(t_game *game)
{
	game->total_collectibles = count_collectibles(game->map);
	game->collectibles_count = game->total_collectibles;
	load_assets(game);
	initialize_player_pos(game);
	initialize_exit_pos(game);
	render_map(game, TILE_SIZE);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 17, 0L, close_window_x, game);
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	load_map(&game);
	create_window(&game);
	initialize_game(&game);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
