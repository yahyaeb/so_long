#include "so_long.h"

#include <fcntl.h> // For open()
#include <stdlib.h> // For malloc() and free()
#include <stdio.h>  // For perror()

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
    while ((line = get_next_line(fd))) // Use your GNL implementation
    {
        map = realloc(map, sizeof(char *) * (i + 2)); // Allocate memory for a new line
        if (!map)
        {
            perror("Error: Memory allocation failed");
            return (NULL);
        }
        map[i++] = line; // Store the line in the array
    }

    if (map)
        map[i] = NULL; // Null-terminate the array
    close(fd);
	
    return (map);
}



void render_map(t_game *game, int tile_size)
{
    for (int y = 0; game->map[y]; y++) // Loop through rows
    {
        for (int x = 0; game->map[y][x]; x++) // Loop through columns
        {
            void *img = NULL;
			printf("here is y: %d and here is x: %d \n", y, x);
            if (game->map[y][x] == '1') // Cone (wall)
                img = game->wall_img;
            else if (game->map[y][x] == '0') // Road
                img = game->empty_img;
			else if (game->map[y][x] == 'C')
				img = game->collectible_img;
			else if (game->map[y][x] == 'P')
				img = game->player_img;
			else if (game->map[y][x] == 'E')
				img = game->exit_img;
				

            if (img)
                mlx_put_image_to_window(game->mlx, game->win, img, x * tile_size, y * tile_size);
        }
    }
}

void print_map(char **map)
{
    for (int i = 0; map[i]; i++)
        printf("%s", map[i]); // Each line already ends with '\n' from GNL
}

int close_window_x(void *mlx_ptr)
{
	close_and_free(mlx_ptr);
	exit(0);
}

int close_window_esc(int keycode, void *param)
{
	(void)param;
	if(keycode == KEY_ESC)
		exit(0);
	return (0);
}
void close_and_free(void *mlx_ptr)
{
    free(mlx_ptr);
    exit(0);
}

// int check_map(const char *file, t_data *data)
// {

// }
void load_assets(t_game *game)
{
    int img_width;
    int img_height;

    game->empty_img = mlx_xpm_file_to_image(game->mlx, "./assets/road_128x128.xpm", &img_width, &img_height);
    game->wall_img = mlx_xpm_file_to_image(game->mlx, "./assets/cone_128x128.xpm", &img_width, &img_height);
	game->collectible_img = mlx_xpm_file_to_image(game->mlx, "./assets/fuel_128x128.xpm", &img_width, &img_height);
    game->player_img = mlx_xpm_file_to_image(game->mlx, "./assets/Player_128x128.xpm", &img_width, &img_height);
	game->exit_img = mlx_xpm_file_to_image(game->mlx, "./assets/door_128x128.xpm", &img_width, &img_height);
	
	if (!game->empty_img || !game->wall_img || !game->collectible_img || !game->player_img || !game->exit_img)
    {
        perror("Error: Failed to load assets");
        exit(1); // Handle the error appropriately
    }
}



int main(void)
{
    t_game game;

    // Initialize MiniLibX
    game.mlx = mlx_init();
    if (!game.mlx)
    {
        perror("Error: Failed to initialize MiniLibX");
        return (1);
    }

    // Parse the map
    game.map = parse_map("map.ber");
    if (!game.map)
    {
        perror("Error: Failed to parse map");
        return (1);
    }

    // Calculate window dimensions based on the map and tile size
    int window_width = strlen(game.map[0]) * TILE_SIZE;
    int window_height = get_map_height(game.map) * TILE_SIZE;

    // Create the game window
    game.win = mlx_new_window(game.mlx, window_width, window_height, "Infinite Runner");
    if (!game.win)
    {
        perror("Error: Failed to create window");
        free(game.map); // Free map memory if window creation fails
        return (free(game.mlx), 1);
    }

    // Load background image
    int bg_width, bg_height;
    game.bg = mlx_xpm_file_to_image(game.mlx, "assets/game_background.xpm", &bg_width, &bg_height);
    if (!game.bg)
    {
        perror("Error: Failed to load background image");
        free(game.map);
        mlx_destroy_window(game.mlx, game.win);
        free(game.mlx);
        return (1);
    }

    // Warn if background image dimensions don't match window size
    if (bg_width != window_width || bg_height != window_height)
    {
        printf("Warning: Background image dimensions (%dx%d) do not match window size (%dx%d)\n",
               bg_width, bg_height, window_width, window_height);
    }

    // Load game assets
    load_assets(&game);

    // Validate map
    if (!validate_map(game.map))
    {
        perror("Error: Invalid map");
        free(game.map);
        mlx_destroy_image(game.mlx, game.bg); // Free background image
        mlx_destroy_window(game.mlx, game.win);
        free(game.mlx);
        return (1);
    }

    // Render the background first
    mlx_put_image_to_window(game.mlx, game.win, game.bg, 0, 0);

    // Render the map on top of the background
    render_map(&game, TILE_SIZE);

    // Set up event hooks
    mlx_hook(game.win, 17, 0L, close_window_x, &game);    // Handle "X" button click
    mlx_hook(game.win, 2, 1L << 0, close_window_esc, &game); // Handle ESC key

    // Start the event loop
    mlx_loop(game.mlx);

    // Cleanup on exit
    free(game.map);
    mlx_destroy_image(game.mlx, game.bg);
    mlx_destroy_window(game.mlx, game.win);
    free(game.mlx);

    return (0);
}
