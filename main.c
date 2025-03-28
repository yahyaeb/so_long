/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 06:42:53 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/03/28 15:38:11 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	check_argv(char *argv)
{
	int	len;

	len = ft_strlen(argv);
	if (len <= 4)
		return (0);
	if (len > 4)
	{
		if (argv[len - 1] != 'r' || argv[len - 2]
			!= 'e' || argv[len - 3] != 'b' || argv[len - 4] != '.')
			return (0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc == 2 && check_argv(argv[1]))
	{
		init_game(&game);
		game.map = parse_map(argv[1]);
		if (!game.map)
			handle_map(&game);
		game.map_copy = copy_map(game.map);
		if (!game.map_copy)
			handle_map_copy(&game);
		if (!validate_map(game.map_copy))
			handle_map_error(&game);
		create_window(&game);
		initialize_game(&game);
		setup_hooks(&game);
		mlx_loop(game.mlx);
	}
	else
		ft_printf("Error: Usage %s <map_file.ber>\n", argv[0]);
	return (0);
}
