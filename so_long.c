/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:43:57 by mrochedy          #+#    #+#             */
/*   Updated: 2024/09/28 17:46:24 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char ***map, int size)
{
	int	i;

	i = 0;
	if (size)
		while (i < size)
			free((*map)[i++]);
	else
		while ((*map)[i])
			free((*map)[i++]);
	free(*map);
}

int	add_one_line(char ***map, int *i, int fd)
{
	char	**tmp;

	tmp = ft_realloc(*map, sizeof(char *) * (*i + 1),
			sizeof(char *) * (*i + 2));
	if (!tmp)
		return (free_map(map, *i + 1), 1);
	*map = tmp;
	(*map)[++(*i)] = get_next_line(fd);
	if (remove_nl(&(*map)[*i]))
		return (free_map(map, *i + 1), 1);
	return (0);
}

char	**read_map(char **argv)
{
	int		fd;
	int		i;
	char	**map;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (close(fd), ft_printf("Error\nMap cannot be parsed\n"), NULL);
	map = malloc(sizeof(char *));
	if (!map)
		return (close(fd), ft_printf("Error\nMemory problem occured\n"), NULL);
	i = 0;
	map[i] = get_next_line(fd);
	if (!map[i])
		return (close(fd), free(map), ft_printf("Error\nMap is empty\n"), NULL);
	if (remove_nl(&map[i]))
		return (close(fd), free_map(&map, 1), NULL);
	while (map[i])
		if (add_one_line(&map, &i, fd))
			return (close(fd), NULL);
	return (close(fd), map);
}

static void	get_map_size(char **map, t_coord *coord)
{
	coord->row = 0;
	coord->col = 0;
	while (map[coord->row])
		coord->row++;
	while (map[coord->row - 1][coord->col])
		coord->col++;
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_coord	map_size;

	if (check_basic_errors(argc, argv))
		return (1);
	game.map = read_map(argv);
	if (!game.map)
		return (1);
	if (check_map_errors(&game))
		return (free_map(&game.map, 0), 1);
	game.data = malloc(sizeof(t_data));
	if (!game.data)
		return (free_map(&game.map, 0), 1);
	game.data->mlx_ptr = mlx_init();
	if (!game.data->mlx_ptr)
		return (free_map(&game.map, 0), 1);
	get_map_size(game.map, &map_size);
	game.data->win_ptr = mlx_new_window(game.data->mlx_ptr,
			map_size.col * IMG_SIZE, map_size.row * IMG_SIZE, "so_long");
	if (!game.data->win_ptr)
		return (free_map(&game.map, 0), free(game.data->mlx_ptr), 1);
	game.moves = 0;
	game.is_error = 0;
	return (game.pos = NULL, manage_window(&game), free(game.data->mlx_ptr),
		safe_free(game.data->imgs), free_map(&game.map, 0), 1);
}
