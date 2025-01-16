#include <stdlib.h>
#include <stdio.h>

#if defined(__APPLE__)
#include "mlx/mlx.h"
#else
#include "mlx/mlx.h"
#endif

#if defined(__APPLE__)
#define KEY_ESC 53  // macOS ESC keycode
#else
#define KEY_ESC 65307  // Linux ESC keycode
#endif

#include "mlx/mlx.h"

typedef struct s_map
{
    int width;
    int height;
    char **data;  // 2D array of the map's characters
} t_map;

typedef struct s_data
{
	void		*mlx_ptr; // MLX pointer
	void		*win_ptr; // MLX window pointer
	void		*textures[5]; // MLX image pointers (on the stack)
	t_map		*map; // Map pointer (contains map details - preferably kept on the stack)
}	t_data;


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