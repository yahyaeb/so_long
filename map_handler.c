#include "so_long.h"

// Get the height of the map
int get_map_height(char **map)
{
    int height = 0;
    while (map && map[height])
        height++;
    return height;
}


// Check if the map is rectangular
int is_rectangular(char **map)
{
    if (!map || !map[0])
        return (printf("Error: Map is empty.\n"), 0);

    int i = 0;
    int row_length = ft_strlen(map[0]);

    while (map[i])
    {
        printf("i: %d\n", i);
        printf("strlen: %d, row_length: %d\n",ft_strlen(map[i]), row_length);
        if (ft_strlen(map[i]) != row_length)
            return (printf("Error: Map is not rectangular.\n"), 0);
        i++;
    }
    return (1);
}

// Check if a row is all walls ('1')
int check_row_walls(char *row)
{
    if (!row)
        return (0);

    int j = 0;
    int row_len = ft_strlen(row) - 1;

    while (j < row_len)
    {
        if(j == 0 || j == row_len)
            {
                if (row[j] != '1')
                {
                    printf("%d", j);
                    return (printf("Error: Row must be all walls ('1').\n"), 0);
                }
            }      
        j++;
    }
    return (1);
}

// Check if the map is surrounded by walls
int has_surrounding_walls(char **map)
{
    if (!map || !map[0])
        return (printf("Error: Map is empty.\n"), 0);

    int i = 1;  // Start from the second row
    int height = get_map_height(map);
    int row_len = ft_strlen(map[0]);

    // Check top and bottom rows
    if (!check_row_walls(map[0]) || !check_row_walls(map[height - 1]))
        return (0);

    // Check left and right walls in each middle row
    while (i < height - 1)
    {
        {
            if(i == 0 || i == height)
            {
                if ((map[i][0] == '1') || (map[i][row_len - 1] != '1'))       
                    return (printf("Error: Map must be surrounded by walls.\n"), 0);
            }
        }
        i++;
    }
    return (1);
}

// Check if the map has required elements
int has_required_elements(char **map)
{
    if (!map)
        return (0);

    int i = 0;
    int j;
    int player_count = 0;
    int exit_count = 0;
    int collectible_count = 0;

    while (map[i])
    {
        j = 0;
        int row_len = ft_strlen(map[i]);
        while (j < row_len)
        {
            if (map[i][j] == 'P')
                player_count++;
            else if (map[i][j] == 'E')
                exit_count++;
            else if (map[i][j] == 'C')
                collectible_count++;
            j++;
        }
        i++;
    }

    if (player_count != 1)
        return (printf("Error: There must be exactly 1 player (P).\n"), 0);
    if (exit_count != 1)
        return (printf("Error: There must be exactly 1 exit (E).\n"), 0);
    if (collectible_count < 1)
        return (printf("Error: There must be at least 1 collectible (C).\n"), 0);

    return (1);
}

// Validate the entire map
int validate_map(char **map)
{
    if (!map)
        return (printf("Error: Map is null.\n"), 0);

    if (!is_rectangular(map))
        return (0);
    if (!has_surrounding_walls(map))
        return (0);
    if (!has_required_elements(map))
        return (0);

    return (1);
}
