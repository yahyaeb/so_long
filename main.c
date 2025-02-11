/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 06:42:53 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/11 17:58:56 by yel-bouk         ###   ########.fr       */
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

	window_width = (ft_strlen(game->map[0]) - 1) * TILE_SIZE;
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
	game->movement_count = 0;
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

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file.ber>\n", argv[0]);
		return (1);
	}
	init_game(&game);

	game.map = parse_map(argv[1]);
	if (!game.map)
		handle_map_error(&game);

	game.map_copy = copy_map(game.map);
	if (!game.map_copy)
		handle_map_error(&game);
	if (!validate_map(game.map_copy))
		handle_map_error(&game);

		
	create_window(&game);
	initialize_game(&game);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
