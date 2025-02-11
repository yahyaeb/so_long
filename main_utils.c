/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:48:49 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/11 17:17:51 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_assets(t_game *game)
{
	int	img_width;
	int	img_height;

	game->textures.wall = mlx_xpm_file_to_image(game->mlx,
			"./textures/cone_background.xpm", &img_width, &img_height);
	game->textures.collectible = mlx_xpm_file_to_image(game->mlx,
			"./textures/star_bg.xpm", &img_width, &img_height);
	game->textures.player = mlx_xpm_file_to_image(game->mlx,
			"./textures/power_ranger_w_bg.xpm", &img_width, &img_height);
	game->textures.exit = mlx_xpm_file_to_image(game->mlx,
			"./textures/door_bg.xpm", &img_width, &img_height);
	game->textures.floor = mlx_xpm_file_to_image(game->mlx,
			"./textures/background_green_tile.xpm", &img_width, &img_height);
	if (!game->textures.player || !game->textures.wall || !game->textures.exit
		|| !game->textures.collectible || !game->textures.floor)
	{
		perror("Error: Failed to load assets");
		exit(1);
	}
}

int	count_collectibles(char **map)
{
	int	i;
	int	j;
	int	collectibles_count;

	i = 0;
	collectibles_count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				collectibles_count++;
			j++;
		}
		i++;
	}
	return (collectibles_count);
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		perror("Error: Failed to initialize MiniLibX");
		exit(1);
	}
}

void	free_map_load(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	load_map(t_game *game)
{
	game->map = parse_map("./map.ber");
	if (!game->map)
		handle_map_error(game);
	game->map_copy = copy_map(game->map);
	if (!game->map_copy)
		handle_map_error(game);
	if (!validate_map(game->map_copy))
		handle_map_error(game);
}
