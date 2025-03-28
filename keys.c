/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:15:50 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/12 12:36:35 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid_move(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_y < 0 || !game->map[new_y] || !game->map[new_y][new_x])
		return (0);
	if (game->map[new_y][new_x] == '1')
		return (0);
	return (1);
}

void	collect_item(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'C')
	{
		game->map[new_y][new_x] = '0';
		game->collectibles_count--;
	}
}

void	handle_exit(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'E')
	{
		if (game->collectibles_count == 0)
		{
			ft_printf("You win! Exiting...\n");
			cleanup_game(game);
			exit(0);
		}
	}
}

void	update_player_position(t_game *game, int new_x, int new_y)
{
	if (game->player_x == game->exit_x
		&& game->player_y == game->exit_y)
		game->map[game->player_y][game->player_x] = 'E';
	else
		game->map[game->player_y][game->player_x] = '0';
	game->player_x = new_x;
	game->player_y = new_y;
	game->player_on_exit = (game->player_on_exit);
	game->map[new_y][new_x] = 'P';
}

int	handle_keypress(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_y = game->player_y;
	new_x = game->player_x;
	get_new_position(keycode, &new_x, &new_y);
	if (keycode == KEY_ESC)
	{
		cleanup_game(game);
		exit(0);
	}
	if (!is_valid_move(game, new_x, new_y))
		return (0);
	if (new_x != game->player_x || new_y != game->player_y)
		ft_printf("Movements counter: %d\n", ++game->movement_count);
	collect_item(game, new_x, new_y);
	handle_exit(game, new_x, new_y);
	update_player_position(game, new_x, new_y);
	mlx_clear_window(game->mlx, game->win);
	render_map(game, TILE_SIZE);
	return (0);
}
