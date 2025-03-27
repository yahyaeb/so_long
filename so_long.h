/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 06:51:27 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/03/27 15:42:39 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "./GNL/get_next_line.h"
# include "ft_printf/includes/ft_printf.h"

# include "mlx/mlx.h"

# define TILE_SIZE 125

# if defined(__linux__)
#  define KEY_W 119       // W key
#  define KEY_A 97        // A key
#  define KEY_S 115       // S key
#  define KEY_D 100       // D key
#  define KEY_ESC 65307   // ESC key
# endif

typedef struct s_flood
{
	int	collectibles_count;
	int	found_exit;
}	t_flood;

typedef struct s_textures
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*collectible;
	void	*exit;
	void	*player_on_exit;
}	t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	char		**map_copy;
	int			map_width;
	int			map_height;
	int			player_x;
	int			player_y;
	int			exit_x;
	int			exit_y;
	int			tile_size;
	t_textures	textures;
	int			collectibles_count;
	int			total_collectibles;
	int			player_on_exit;
	int			movement_count;
}	t_game;

/* ---------------------- Map Validation ---------------------- */
int		get_map_height(char **map);
int		is_rectangular(char **map);
int		check_row_walls(char *row);
int		has_surrounding_walls(char **map);
int		has_required_elements(char **map);
int		validate_map(char **map);
int		has_invalid_char(char **map);
int		is_valid_move_table(char **map, int x, int y);
int		flood_fill(char **map, int x, int y, t_flood *flood);
char	**allocate_map(int line_count);

/* ---------------------- Map Parsing ---------------------- */
char	**copy_map(char **map);
char	**parse_map(const char *file_path);

/* ---------------------- File Handling ---------------------- */
int		open_file(const char *file_path);
int		count_lines(const char *file_path);
void	read_lines(int fd, char **map);
char	*get_next_line(int fd);

/* ---------------------- Memory Management ---------------------- */
void	free_map_memory(char **map, int size);
void	free_map(char **map);
void	free_map_load(char **map);
void	close_and_free(void *mlx_ptr);
void	handle_map_error(t_game *game);

/* ---------------------- Game Initialization ---------------------- */
void	init_game(t_game *game);
void	load_map(t_game *game);
void	initialize_exit_pos(t_game *game);
void	initialize_player_pos(t_game *game);

/* ---------------------- Rendering & UI ---------------------- */
void	render_map(t_game *game, int tile_size);
void	load_assets(t_game *game);
void	check_image_size(void *mlx, char *path);

/* ---------------------- Game Logic ---------------------- */
void	get_player_position(char **map, int *x, int *y);
int		is_valid_move(t_game *game, int new_x, int new_y);
void	get_new_position(int keycode, int *new_x, int *new_y);
int		count_collectibles(char **map);
int		count_checker(int *player_count, int *exit_count,
			int *collectible_count);
int		check_exceeding_counts(int *player_count, int *exit_count);

/* ---------------------- Player Movement ---------------------- */
void	update_player_position(t_game *game, int new_x, int new_y);
void	collect_item(t_game *game, int new_x, int new_y);
void	handle_exit(t_game *game, int new_x, int new_y);
int		handle_keypress(int keycode, t_game *game);

/* ---------------------- Window & Cleanup ---------------------- */
int		close_window_x(void *mlx_ptr);
int		close_window_esc(int keycode, void *param);
void	cleanup_game(t_game *game);
void	handle_map(t_game *game);
void	handle_map_copy(t_game *game);

#endif
