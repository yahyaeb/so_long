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

int main(void)
{
	void *mlx_ptr;
	void *win_ptr;
	

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (1);
	win_ptr = mlx_new_window(mlx_ptr, 1000, 500, "hi :)");
	if (!win_ptr)
		return (free(mlx_ptr), 1);

	/******** Image ptr********/
	void *bg_img;
	int bg_height;
	int bg_width;


	bg_img = mlx_xpm_file_to_image(mlx_ptr, "assets/game_background.xpm", &bg_width, &bg_height);
	if(!bg_img)
	{
		perror("Error: Failed to load image\n");
		close_and_free(mlx_ptr);
		return (1);
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, bg_img, 0, 0);
	/**************************/

/*-------map parsing---------*/
    char **map = parse_map("map.ber");
    if (!map)
        return (1);

    // Print the map for debugging
    if (validate_map(map))
        print_map(map);
    else {
        for (int i = 0; map[i]; i++)
            free(map[i]);
        free(map);
    }
/*--------------------------*/


	mlx_hook(win_ptr, 17, 0L, close_window_x, NULL);  // Exit when "X" button is clicked
	mlx_hook(win_ptr, 2, 1L << 0, close_window_esc, NULL);
	mlx_loop(mlx_ptr);
	
	mlx_destroy_image(mlx_ptr, bg_img);
	close_and_free(mlx_ptr);

	return (0);
}