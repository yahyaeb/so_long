/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 06:54:31 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/11 10:52:07 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	count_elements(char **map, int *player_count,
	int *exit_count, int *collectible_count)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (j < ft_strlen(map[i]))
		{
			if (map[i][j] == 'P')
				(*player_count)++;
			else if (map[i][j] == 'E')
				(*exit_count)++;
			else if (map[i][j] == 'C')
				(*collectible_count)++;
			if (check_exceeding_counts(player_count, exit_count) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	has_invalid_char(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != 'P' && map[i][j] != 'E' &&
				map[i][j] != 'C' && map[i][j] != '0' &&
				map[i][j] != '1' && map[i][j] != '\n')
			{
				ft_printf("Error: Map is not properly enclosed by walls.");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	has_required_elements(char **map)
{
	int	player_count;
	int	exit_count;
	int	collectible_count;

	player_count = 0;
	exit_count = 0;
	collectible_count = 0;
	if (!map)
		return (0);
	if (count_elements(map, &player_count,
			&exit_count, &collectible_count) == 0)
		return (0);
	if (count_checker(&player_count,
			&exit_count, &collectible_count) == 0)
		return (0);
	return (1);
}

int	check_exceeding_counts(int *player_count, int *exit_count)
{
	if (*player_count > 1)
	{
		ft_printf("Error: There must be exactly 1 player (P).\n");
		return (0);
	}
	if (*exit_count > 1)
	{
		ft_printf("Error: There must be exactly 1 exit (E).\n");
		return (0);
	}
	return (1);
}
