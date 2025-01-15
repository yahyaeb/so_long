#include "so_long.h"

int get_map_height(char **map)
{
    int height;

    height = 0;
    while(map[height])
        height++;
    return height;
}

int is_rectangular(char **map)
{
    int i;
    int row_len;

    i = 0;
    row_len = ft_strlen(map[0]);
    while(map[i]) 
    {
        if(ft_strlen(map[i]) != row_len)
        {
            perror("Error: Map must be rectangular\n");
            return 1;
        }
        i++;
    }
    return 0;
}

int check_row_walls(char *row)
{
    int j = 0;
    int row_len = ft_strlen(row);  // Get the length of the row

    while (j < row_len)
    {
        if (row[j] != '1')  // Check if the character is not '1'
        {
            printf("Error: Row must be surrounded by walls (all '1's).\n");
            return (0);  // Invalid row
        }
        j++;
    }
    return (1);  // Row is valid
}

int has_surrounding_walls(char **map)
{
    int i = 1;  // Start from the second row
    int height = get_map_height(map);  // Get the height of the map
    int row_len = ft_strlen(map[0]);

    // Check top and bottom rows
    if (!check_row_walls(map[0]) || !check_row_walls(map[height - 1]))
        return (0);  // Error if the top or bottom row is not all '1'

    // Check left and right walls in each middle row
    while (i < height - 1)
    {
        if (map[i][0] != '1' || map[i][row_len - 1] != '1')  // Check side walls
        {
            printf("Error: Map must be surrounded by walls (side walls).\n");
            return (0);
        }
        i++;
    }

    return (1);  // Map is valid
}

int has_required_elements(char **map)
{
  int i;
  int j;
  int player_count;
  int exit_count;
  int collectible_count;

    i = 0;
    player_count =0;
    exit_count = 0;
    collectible_count = 0;
  while(map[i])
  {
    j = 0;
    while(j < ft_strlen(map[i]))
    {
        if (map[i][j] == 'P')
            player_count++;
        else if(map[i][j] == 'E')
            exit_count++;
        else if (map[i][j] == 'C')
            collectible_count++;
        j++;
    }
    i++;
  }
    if (player_count != 1)
        return (printf("Error: There must be exactly 1 player (P)\n"), 0);
    if (exit_count < 1)
        return (printf("Error: There must be at least 1 exit (E)\n"), 0);
    if (collectible_count < 1)
        return (printf("Error: There must be at least 1 collectible (C)\n"), 0);

    return 1;
}
int validate_map(char **map)
{
    if (!is_rectangular(map))
        return 0;
    if (!has_surrounding_walls(map))
        return 0;
    if (!has_required_elements(map))
        return 0;
    return 1;
}