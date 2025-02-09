/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 06:54:31 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/09 13:45:54 by yel-bouk         ###   ########.fr       */
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
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != 'P' && map[i][j] != 'E' &&
				map[i][j] != 'C' && map[i][j] != '0' && map[i][j] != '1' && map[i][j] != '\n')
			{
				printf("Error: Invalid character '%c' found in map.\n", map[i][j]);
				return (1); // Found an invalid character
			}
			j++;
		}
		i++;
	}
	return (0); // No invalid characters found
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
		printf("Error: There must be exactly 1 player (P).\n");
		return (0);
	}
	if (*exit_count > 1)
	{
		printf("Error: There must be exactly 1 exit (E).\n");
		return (0);
	}
	return (1);
}

int	validate_map_structure(char **map)
{
	if (!map)
	{
		perror("Error: Map is null.\n");
		return (0);
	}
	if (!is_rectangular(map))
		return (0);
	if (has_invalid_char(map))
	{
		printf("invalid chars\n");	
		return (0);	
	}
	if (!has_surrounding_walls(map))
	{
		printf("Error: Map is not properly enclosed by walls.\n");
		return (0);
	}
	if (!has_required_elements(map))
	{
		printf("Error: Missing required elements.\n");
		return (0);
	}
	return (1);
}

int	validate_map(char **map)
{
	int	px;
	int	py;
	t_flood flood;

	flood.collectibles_count = 0;
	flood.found_exit = 0;
	get_player_position(map, &px, &py);

	if (!validate_map_structure(map))
		return (0);
	if (!flood_fill(map, px, py, &flood))
	{
		print_map(map);
		printf("Error: Not all collectibles are reachable, or no path to exit.\n");
		return (0);
	}
	return (1);
}
