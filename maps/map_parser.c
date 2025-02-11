/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:25:16 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/11 11:48:56 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	render_objects(t_game *game, int x, int y, int tile_size)
{
	if (game->map[y][x] == '1')
		mlx_put_image_to_window(game->mlx, game->win,
			game->textures.wall, x * tile_size, y * tile_size);
	else if (game->map[y][x] == 'C')
		mlx_put_image_to_window(game->mlx, game->win,
			game->textures.collectible, x * tile_size, y * tile_size);
	else if (game->map[y][x] == 'P')
		mlx_put_image_to_window(game->mlx, game->win,
			game->textures.player, x * tile_size, y * tile_size);
}

void	render_map(t_game *game, int tile_size)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			mlx_put_image_to_window(game->mlx, game->win,
				game->textures.floor, x * tile_size, y * tile_size);
			render_objects(game, x, y, tile_size);
			x++;
		}
		y++;
	}
	if (game->collectibles_count == 0)
		mlx_put_image_to_window(game->mlx, game->win, game->textures.exit,
			game->exit_x * tile_size, game->exit_y * tile_size);
}

char	**parse_map(const char *file_path)
{
	int		fd;
	int		line_count;
	char	**map;

	line_count = count_lines(file_path);
	if (line_count < 0)
		return (NULL);
	map = allocate_map(line_count);
	if (!map)
		return (NULL);
	fd = open_file(file_path);
	if (fd < 0)
	{
		free(map);
		return (NULL);
	}
	read_lines(fd, map);
	close(fd);
	return (map);
}

char	**copy_map(char **map)
{
	int		height;
	int		i;
	char	**map_copy;

	height = get_map_height(map);
	map_copy = malloc((height + 1) * sizeof(char *));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
		{
			while (i > 0)
				free(map_copy[--i]);
			free(map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[height] = NULL;
	return (map_copy);
}
