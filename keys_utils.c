/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:37:18 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/07 11:38:34 by yel-bouk         ###   ########.fr       */
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
