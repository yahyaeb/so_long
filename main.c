/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 06:42:53 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/07 11:19:43 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"



void load_assets(t_game *game)
{
    int img_width;
    int img_height;

    game->textures.wall = mlx_xpm_file_to_image(game->mlx, "./assets/cone_background.xpm", &img_width, &img_height);
	game->textures.collectible = mlx_xpm_file_to_image(game->mlx, "./assets/star_bg.xpm", &img_width, &img_height);
    game->textures.player = mlx_xpm_file_to_image(game->mlx, "./assets/power_ranger_w_bg.xpm", &img_width, &img_height);
	game->textures.exit = mlx_xpm_file_to_image(game->mlx, "./assets/door_bg.xpm", &img_width, &img_height);
    game->textures.floor = mlx_xpm_file_to_image(game->mlx, "./assets/background_green_tile.xpm", &img_width, &img_height);
	
	if (!game->textures.player || !game->textures.wall || !game->textures.exit || !game->textures.collectible || !game->textures.floor)
    {
        perror("Error: Failed to load assets");
        exit(1);
    }
}

int    count_collectibles(char **map)
{
    int i = 0;
    int j;

    int collectibles_count = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if(map[i][j] == 'C')
                collectibles_count++;
            j++;
        }
        i++;
    }
    return collectibles_count;
}

void initialize_player_pos(t_game *game)
{
    int i;
    int k;

    i = 0;
    while(game->map[i])
    {
        k = 0;
        while(game->map[i][k])
        {
            if (game->map[i][k] == 'P')
            {
                game->player_x = k;
                game->player_y = i;
                return;
            }
            k++;
        }
        i++;
    }
}

void initialize_exit_pos(t_game *game)
{
    int i;
    int k;
    
    game->exit_x = -1;
    game->exit_y = -1;
    i = 0;
    while(game->map[i])
    {
        k = 0;
        while(game->map[i][k])
        {
            if (game->map[i][k] == 'E')
            {
                game->exit_x = k;
                game->exit_y = i;
                return;
            }
            k++;
        }
        i++;
    }
}

int main(void)
{
    t_game game;
    memset(&game, 0, sizeof(t_game));

    // Initialize MiniLibX
    game.mlx = mlx_init();
    if (!game.mlx)
    {
        perror("Error: Failed to initialize MiniLibX");
        return (1);
    }

    // Parse the map
    game.map = parse_map("map/map.ber");
    if (!game.map)
    {
        perror("Error: Failed to parse map");
        cleanup_game(&game);
        return (1);
    }

    game.map_copy = copy_map(game.map);
    if (!game.map_copy)
    {
        perror("Error: Failed to copy map");
        cleanup_game(&game);
        return (1);
    }

    // Validate the map BEFORE creating the window
    if (!validate_map(game.map_copy))
    {
        cleanup_game(&game);
        return (1);
    }

    // Calculate window dimensions
    int window_width = (strlen(game.map[0]) - 1) * TILE_SIZE;
    int window_height = get_map_height(game.map) * TILE_SIZE;

    // Create the game window
    game.win = mlx_new_window(game.mlx, window_width, window_height, "So Long");
    if (!game.win)
    {
        perror("Error: Failed to create window");
        cleanup_game(&game);
        return (1);
    }

    game.total_collectibles = count_collectibles(game.map);
    game.collectibles_count = game.total_collectibles;

    // Load game assets
    load_assets(&game);

    // Initialize the player's position
    initialize_player_pos(&game);
    initialize_exit_pos(&game);

    // Render the map
    render_map(&game, TILE_SIZE);

    // Set up event hooks
    mlx_hook(game.win, 17, 0L, close_window_x, &game);
    mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);

    // Handle CTRL+C to prevent leaks
    // Start the event loop
    mlx_loop(game.mlx);

    return (0); // No need for cleanup_game here
}
