#include <stdlib.h>

#if defined(__APPLE__)
#include "mlx/mlx.h"
#else
#include "minilibx-linux/mlx.h"
#endif

int main(void)
{
	void *mlx_ptr;

	mlx_ptr = mlx_init();  // Initialize graphics library
	if (!mlx_ptr)
		return (1);
	return (0);
}
