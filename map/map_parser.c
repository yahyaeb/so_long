/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:25:16 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/07 11:14:03 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void render_map(t_game *game, int tile_size)
{
    int y = 0;
    while (game->map[y])
    {
        int x = 0;
        while (game->map[y][x])
        {
            mlx_put_image_to_window(game->mlx, game->win, game->textures.floor, x * tile_size, y * tile_size);

            if (game->map[y][x] == '1') // Wall
                mlx_put_image_to_window(game->mlx, game->win, game->textures.wall, x * tile_size, y * tile_size);
            else if (game->map[y][x] == 'C') // Collectible
                mlx_put_image_to_window(game->mlx, game->win, game->textures.collectible, x * tile_size, y * tile_size);
            else if (game->map[y][x] == 'P') // Player
                mlx_put_image_to_window(game->mlx, game->win, game->textures.player, x * tile_size, y * tile_size);

            x++;
        }
        y++;
    }
    if (game->collectibles_count == 0)
    {
        mlx_put_image_to_window(
            game->mlx,
            game->win,
            game->textures.exit,
            game->exit_x * tile_size,
            game->exit_y * tile_size
        );
    }
}

char **parse_map(const char *file_path)
{
    int fd = open(file_path, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening map file");
        return (NULL);
    }

    char **map = NULL;
    char *line;
    int i = 0;

    while ((line = get_next_line(fd))) 
    {
        if (line[0] == '\n' || line[0] == '\0')
        {
            free(line);
            continue;
        }
        char **temp = realloc(map, sizeof(char *) * (i + 2));
        if (!temp)
        {
            perror("Error: Memory allocation failed");
            while (i > 0)
                free(map[--i]);
            free(map);
            free(line);
            close(fd);
            return (NULL);
        }
        map = temp;
        map[i++] = line;
    }

    if (map)
        map[i] = NULL;

    close(fd);
    return (map);
}