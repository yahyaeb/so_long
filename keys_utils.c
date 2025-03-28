/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:37:18 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/12 12:39:53 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_new_position(int keycode, int *new_x, int *new_y)
{
	if (keycode == KEY_W)
		(*new_y) -= 1;
	else if (keycode == KEY_S)
		(*new_y) += 1;
	else if (keycode == KEY_A)
		(*new_x) -= 1;
	else if (keycode == KEY_D)
		(*new_x) += 1;
}

void	initialize_player_pos(t_game *game)
{
	int	i;
	int	k;

	i = 0;
	while (game->map[i])
	{
		k = 0;
		while (game->map[i][k])
		{
			if (game->map[i][k] == 'P')
			{
				game->player_x = k;
				game->player_y = i;
				return ;
			}
			k++;
		}
		i++;
	}
}

void	initialize_exit_pos(t_game *game)
{
	int	i;
	int	k;

	i = 0;
	while (game->map[i])
	{
		k = 0;
		while (game->map[i][k])
		{
			if (game->map[i][k] == 'E')
			{
				game->exit_x = k;
				game->exit_y = i;
				return ;
			}
			k++;
		}
		i++;
	}
}

void	handle_map(t_game *game)
{
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(1);
}

void	handle_map_copy(t_game *game)
{
	free_map(game->map);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(1);
}
