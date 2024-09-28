/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:21:02 by mrochedy          #+#    #+#             */
/*   Updated: 2024/07/02 11:01:06 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
	map_sizes[0] = rows;
	map_sizes[1] = cols;
*/

static char	**prepare_copy(char **map, int *map_sizes)
{
	char	**map_copy;

	map_sizes[0] = 0;
	map_sizes[1] = 0;
	while (map[map_sizes[0]])
		map_sizes[0]++;
	map_copy = malloc(sizeof(char *) * (map_sizes[0] + 1));
	if (!map_copy)
		return (NULL);
	while (map[0][map_sizes[1]])
		map_sizes[1]++;
	map_copy[map_sizes[0]--] = NULL;
	return (map_copy);
}

static char	**copy_map(char **map)
{
	char	**map_copy;
	int		map_sizes[2];
	int		j;

	map_copy = prepare_copy(map, map_sizes);
	if (!map_copy)
		return (NULL);
	while (map_sizes[0]-- >= 0)
	{
		map_copy[map_sizes[0] + 1] = malloc(sizeof(char) * (map_sizes[1] + 1));
		if (!map_copy[map_sizes[0] + 1])
			return (free_map(&map_copy, 0), NULL);
		j = 0;
		while (map[map_sizes[0] + 1][j++])
		{
			if (map[map_sizes[0] + 1][j - 1] != '1'
				&& map[map_sizes[0] + 1][j - 1] != 'e')
				map_copy[map_sizes[0] + 1][j - 1] = '0';
			else
				map_copy[map_sizes[0] + 1][j - 1] = '1';
		}
	}
	return (map_copy);
}

static void	flood_fill(char **map, int row, int col)
{
	if (map[row][col] == '1')
		return ;
	map[row][col] = '1';
	flood_fill(map, row + 1, col);
	flood_fill(map, row - 1, col);
	flood_fill(map, row, col - 1);
	flood_fill(map, row, col + 1);
}

static void	get_entry_coord(char **map, t_coord *coord)
{
	coord->row = 0;
	while (map[coord->row])
	{
		coord->col = 0;
		while (map[coord->row][coord->col])
		{
			if (map[coord->row][coord->col] == 'P')
				return ;
			(coord->col)++;
		}
		(coord->row)++;
	}
}

int	check_valid_path(char **map)
{
	char	**map_copy;
	t_coord	entry_coord;
	t_coord	coord;

	map_copy = copy_map(map);
	if (!map_copy)
		return (ft_printf("Error\nSomething went wrong.\n"), 1);
	get_entry_coord(map, &entry_coord);
	flood_fill(map_copy, entry_coord.row, entry_coord.col);
	coord.row = 0;
	while (map[coord.row++])
	{
		coord.col = 0;
		while (map[coord.row - 1][coord.col++])
			if (map[coord.row - 1][coord.col - 1] == 'C' ||
				map[coord.row - 1][coord.col - 1] == 'E')
				if (map_copy[coord.row - 1][coord.col - 1] != '1')
					return (free_map(&map_copy, 0),
						ft_printf("Error\nMap should have a valid path.\n"), 1);
	}
	return (free_map(&map_copy, 0), 0);
}
