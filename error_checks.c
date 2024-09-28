/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:25:50 by mrochedy          #+#    #+#             */
/*   Updated: 2024/09/28 17:45:59 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_basic_errors(int argc, char **argv)
{
	int	map_len;

	if (argc > 2)
		return (ft_printf("Error\nToo many arguments.\n"), 1);
	else if (argc < 2)
		return (ft_printf("Error\nYou need to pass a map as argument\n"), 1);
	map_len = ft_strlen(argv[1]);
	if (argv[1][map_len - 4] != '.' || argv[1][map_len - 3] != 'b' ||
		argv[1][map_len - 2] != 'e' || argv[1][map_len - 1] != 'r')
		return (ft_printf("Error\nMap needs to be a .ber file\n"), 1);
	return (0);
}

static int	is_valid_char(char c)
{
	int	i;

	i = 0;
	while (VALID_CHARS[i])
		if (c == VALID_CHARS[i++])
			return (1);
	return (0);
}

/*
	indexes[0] = i;
	indexes[1] = j;
	ecp[0] = E;
	ecp[1] = C;
	ecp[2] = P;
*/

static void	set_ecp(int *ecp)
{
	ecp[0] = 0;
	ecp[1] = 0;
	ecp[2] = 0;
}

static int	check_valid_chars(t_game *game)
{
	int	indexes[2];
	int	ecp[3];

	indexes[0] = 0;
	set_ecp(ecp);
	while (game->map[indexes[0]++])
	{
		indexes[1] = 0;
		while (game->map[indexes[0] - 1][indexes[1]++])
		{
			if (!is_valid_char(game->map[indexes[0] - 1][indexes[1] - 1]))
				return (ft_printf("Error\nMap has illegal characters\n"), 1);
			if (game->map[indexes[0] - 1][indexes[1] - 1] == 'E')
				ecp[0]++;
			else if (game->map[indexes[0] - 1][indexes[1] - 1] == 'C')
				ecp[1]++;
			else if (game->map[indexes[0] - 1][indexes[1] - 1] == 'P')
				ecp[2]++;
		}
	}
	if (!ecp[0] || ecp[0] > 1 || !ecp[2] || ecp[2] > 1)
		return (ft_printf("Error\nMap must contain 1 entry and 1 exit\n"), 1);
	if (!ecp[1])
		return (ft_printf("Error\nMap must have at least 1 collectible\n"), 1);
	return (game->collectibles = ecp[1], game->eaten = 0, 0);
}

int	check_map_errors(t_game *game)
{
	size_t	i;
	size_t	j;
	size_t	width;

	i = 0;
	width = ft_strlen(game->map[i++]);
	while (game->map[i])
		if (ft_strlen(game->map[i++]) != width)
			return (ft_printf("Error\nMap should be rectangular\n"), 1);
	j = 0;
	while (game->map[i - 1][j])
		if (game->map[i - 1][j++] != '1')
			return (ft_printf("Error\nMap should be surrounded by walls\n"), 1);
	while (i-- > 1)
		if (game->map[i][0] != '1' || game->map[i][width - 1] != '1')
			return (ft_printf("Error\nMap should be surrounded by walls\n"), 1);
	while (j-- > 0)
		if (game->map[i][j] != '1')
			return (ft_printf("Error\nMap should be surrounded by walls\n"), 1);
	if (check_valid_chars(game) || check_valid_path(game->map))
		return (1);
	return (0);
}
