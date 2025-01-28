#include "so_long.h"



char **parse_map(const char *file_path)
{
    int fd = open(file_path, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening map file");
        close(fd);
        return (NULL);
    }

    char **map = NULL;
    char *line;
    int i = 0;
    while ((line = get_next_line(fd))) 
    {
        char **temp = realloc(map, sizeof(char *) * (i + 2));
        if (!temp)
        {
            perror("Error: Memory allocation failed");
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

    // Always render the exit if all collectibles are collected
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

int close_window_x(void *mlx_ptr)
{
	cleanup_game(mlx_ptr);
	exit(0);
}

int close_window_esc(int keycode, void *param)
{
	(void)param;
	if(keycode == KEY_ESC)
		exit(0);
	return (0);
}

void load_assets(t_game *game)
{
    int img_width;
    int img_height;

    game->textures.wall = mlx_xpm_file_to_image(game->mlx, "./assets/cone_background.xpm", &img_width, &img_height);
	game->textures.collectible = mlx_xpm_file_to_image(game->mlx, "./assets/star_bg.xpm", &img_width, &img_height);
    game->textures.player = mlx_xpm_file_to_image(game->mlx, "./assets/power_ranger_w_bg.xpm", &img_width, &img_height);
	game->textures.exit = mlx_xpm_file_to_image(game->mlx, "./assets/door_bg.xpm", &img_width, &img_height);
    game->textures.floor = mlx_xpm_file_to_image(game->mlx, "./assets/background_green_tile.xpm", &img_width, &img_height);
	
	if (!game->textures.player || !game->textures.wall || !game->textures.exit || !game->textures.collectible)
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

    i = 0;
    while(game->map[i])
    {
        k = 0;
        while(game->map[i][k])
        {
            if (game->map[i][k] == 'E')
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
int handle_keypress(int keycode, t_game *game)
{
    int new_x = game->player_x;
    int new_y = game->player_y;


    if (keycode == KEY_W)
        new_y -= 1;
    else if (keycode == KEY_S)
        new_y += 1;
    else if (keycode == KEY_A)
        new_x -= 1;
    else if (keycode == KEY_D)
        new_x += 1;
    else if (keycode == KEY_ESC) 
    {
        cleanup_game(game);
        exit(0);
    }

    if (new_x < 0 || new_y < 0 || !game->map[new_y] || !game->map[new_y][new_x])
        return (0); 

    if (game->map[new_y][new_x] == '1')
        return (0);
    game->collectibles_count = count_collectibles(game->map);

    if (game->map[new_y][new_x] == 'C')
    {
        game->map[new_y][new_x] = '0';
        game->collectibles_count--; 
        printf("Collectible picked! Remaining: %d\n", game->collectibles_count);
    }


printf("game->map letter: %c\n", game->map[new_y][new_x]);
if (game->map[new_y][new_x] == 'E') 
{
    printf("I am here 0");
    if (new_x == game->exit_x && new_y == game->exit_y && game->collectibles_count == 0)
    {   
        printf("You win! Exiting...\n");
        cleanup_game(game);
        exit(0);
    }
    else
        printf("Collect all collectibles before exiting!\n");
}


    game->map[game->player_y][game->player_x] = '0'; // Clear old position
    game->player_x = new_x;
    game->player_y = new_y;

    // If the player is standing on the door, keep it as 'E'
    if (new_x == game->exit_x && new_y == game->exit_y && game->collectibles_count != 0)
    {
        printf("I am here 1\n");
        game->map[new_y][new_x] = 'P';
        printf("Player is on the exit!\n");
    }
    else
    {
        if (new_x == game->exit_x && new_y == game->exit_y && game->collectibles_count == 0)
    {   
        printf("You win! Exiting...\n");
        cleanup_game(game);
        exit(0);
    }
        printf("I am here 2\n");
        game->map[new_y][new_x] = 'P'; // Update to player position
    }

    mlx_clear_window(game->mlx, game->win);
    render_map(game, TILE_SIZE);

    return (0);
}

void    cleanup_game(t_game *game)
{
    int i;

    i = 0;
    while(game->map[i])
    {
        free(game->map[i]);
        i++;
    }
    // Free the map array itself
    free(game->map);

    // Free all textures if loaded
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

    // Destroy the game window and MLX instance
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx)
        free(game->mlx);
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
        cleanup_game(&game);
        return (1);
    }

    // Calculate window dimensions based on the map and tile size
    int window_width = strlen(game.map[0]) * TILE_SIZE;
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

    // Validate the map
    if (!validate_map(game.map))
    {
        perror("Error: Invalid map");
        cleanup_game(&game);
        return (1);
    }

    // Initialize the player's position
    initialize_player_pos(&game);
    initialize_exit_pos(&game);

    // Render the map
    render_map(&game, TILE_SIZE);

    // Set up event hooks
    mlx_hook(game.win, 17, 0L, close_window_x , &game);    // Handle "X" button click
    mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game); // Handle key presses

    // Start the event loop
    mlx_loop(game.mlx);

    // Cleanup on exit
    cleanup_game(&game);
    return (0);
}
