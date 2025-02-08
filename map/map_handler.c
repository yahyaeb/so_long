/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 06:54:31 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/08 09:28:17 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	has_required_elements(char **map)
{
	int	i;
	int	j;
	int	player_count;
	int	exit_count;
	int	collectible_count;

	i = 0;
	j = 0;
	player_count = 0;
	exit_count = 0;
	collectible_count = 0;
	if (!map)
		return (0);
	while (map[i])
	{
		j = 0;
		while (j < ft_strlen(map[i]))
		{
			if (map[i][j] == 'P')
				player_count++;
			else if (map[i][j] == 'E')
				exit_count++;
			else if (map[i][j] == 'C')
				collectible_count++;
			if (check_exceeding_counts(&player_count, &exit_count) == 0)
				return (0);
			j++;
		}
		i++;
	}
	if (count_checker(&player_count, &exit_count, &collectible_count) == 0)
		return (0);
	return (1);
}

int	check_exceeding_counts(int *player_count, int *exit_count)
{
	if (*player_count > 1)
	{
		perror("Error: There must be exactly 1 player (P).\n");
		return (0);
	}
	if (*exit_count > 1)
	{
		perror("Error: There must be exactly 1 exit (E).\n");
		return (0);
	}
	return (1);
}

char	**copy_map(char **map)
{
	int		height;
	int		i;
	char	**map_copy;

	height = get_map_height(map);
	map_copy = malloc((height + 1) * sizeof(char *));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
		{
			while (i > 0)
				free(map_copy[--i]);
			free(map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[height] = NULL;
	return (map_copy);
}

int 	validate_map(char **map)
{
	int	px;
	int	py;
	int	collectibles_count;
	int	found_exit;
	int	total_collectibles;

	total_collectibles = count_collectibles(map);
	found_exit = 0;
	collectibles_count = 0;
	get_player_position(map, &px, &py);
	if (!map)
	{
		perror("Error: Map is null.\n");
		return (0);
	}
	if (!is_rectangular(map))
		return (0);
	if (!has_surrounding_walls(map))
	{
		perror("Error: Map is not properly enclosed by walls.\n");
		return (0);
	}
	if (!has_required_elements(map))
	{
		printf("Error: Missing required elements.\n");
		return (0);
	}
	if (!flood_fill(map, px, py, &collectibles_count, total_collectibles, &found_exit))
	{
		printf("Error: Not all collectibles are reachable, or no path to exit.\n");
		return (0);
	}
	return (1);
}
