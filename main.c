#include "so_long.h"

int close_window_x(void *param)
{
	(void)param;
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
    mlx_destroy_display(mlx_ptr);
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
	win_ptr = mlx_new_window(mlx_ptr, 1100, 1800, "hi :)");
	if (!win_ptr)
		return (free(mlx_ptr), 1);

	mlx_hook(win_ptr, 17, 0L, close_window_x, NULL);  // Exit when "X" button is clicked
	mlx_hook(win_ptr, 2, 1L << 0, close_window_esc, NULL);
	mlx_loop(mlx_ptr);

	close_and_free(mlx_ptr);

	return (0);
}