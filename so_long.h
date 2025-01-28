#include <stdlib.h>
#include <stdio.h>
#include "./GNL/get_next_line.h"
#if defined(__APPLE__)
#include "mlx/mlx.h"
#else
#include "mlx/mlx.h"
#endif

#define TILE_SIZE 128 

// #if defined(__APPLE__)
// # define KEY_W 13  // W key
// # define KEY_A 0   // A key
// # define KEY_S 1   // S key
// # define KEY_D 2   // D key
// # define KEY_ESC 53 // ESC key
// #endif

#if defined(__linux__)
# define KEY_W 119  // W key
# define KEY_A 97   // A key
# define KEY_S 115  // S key
# define KEY_D 100  // D key
# define KEY_ESC 65307 // ESC key
#endif


#include "mlx/mlx.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h> 

typedef struct s_textures
{
    void *wall;
    void *floor;
    void *player;
    void *collectible;
    void *exit;
    void *player_on_exit;
} t_textures;

typedef struct s_game
{
    // MiniLibX pointers
    void         *mlx;
    void         *win;

    // Map data
    char         **map;
    int          map_width;
    int          map_height;

    // Player data
    int          player_x;
    int          player_y;

    // Tile size
    int          tile_size;

    // Textures
    t_textures   textures;

    // Game state
    int          collectibles_count;
    int          steps;
} t_game;



int	ft_strlen(const char *str);

/*----------------map validator------------------*/
int get_map_height(char **map);                   
int is_rectangular(char **map);
int check_row_walls(char *row);
int has_surrounding_walls(char **map);
int has_required_elements(char **map);
int validate_map(char **map);
int close_window_x(void *mlx_ptr);
int close_window_esc(int keycode, void *param);
void close_and_free(void *mlx_ptr);
/*-----------------------------------------------*/

char	*get_next_line(int fd);
void load_assets(t_game *game);
void render_map(t_game *game, int tile_size);
void check_image_size(void *mlx,  char *path);

void cleanup_game(t_game *game);
int    count_collectibles(char **game);