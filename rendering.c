/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:44:12 by mrochedy          #+#    #+#             */
/*   Updated: 2024/09/28 16:38:37 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_exit(t_game *game)
{
	t_coord	coord;

	coord.row = 0;
	while (game->map[coord.row])
	{
		coord.col = 0;
		while (game->map[coord.row][coord.col])
		{
			if (game->map[coord.row][coord.col] == 'E')
			{
				render_square(game, &coord, 'E');
				return ;
			}
			(coord.col)++;
		}
		(coord.row)++;
	}
}

void	render_square(t_game *game, t_coord *coord, char type)
{
	if (type == '0')
		mlx_put_image_to_window(game->data->mlx_ptr, game->data->win_ptr,
			game->data->imgs->ground, coord->col * IMG_SIZE,
			coord->row * IMG_SIZE);
	if (type == 'C')
		mlx_put_image_to_window(game->data->mlx_ptr, game->data->win_ptr,
			game->data->imgs->collectible, coord->col * IMG_SIZE,
			coord->row * IMG_SIZE);
	if (type == '1')
		mlx_put_image_to_window(game->data->mlx_ptr, game->data->win_ptr,
			game->data->imgs->wall, coord->col * IMG_SIZE,
			coord->row * IMG_SIZE);
	if (type == 'E')
		mlx_put_image_to_window(game->data->mlx_ptr, game->data->win_ptr,
			game->data->imgs->exit, coord->col * IMG_SIZE,
			coord->row * IMG_SIZE);
	if (type == 'e')
		mlx_put_image_to_window(game->data->mlx_ptr, game->data->win_ptr,
			game->data->imgs->enemy, coord->col * IMG_SIZE,
			coord->row * IMG_SIZE);
	if (type == 'P')
		mlx_put_image_to_window(game->data->mlx_ptr, game->data->win_ptr,
			game->data->imgs->player, coord->col * IMG_SIZE,
			coord->row * IMG_SIZE);
}

static int	get_player_pos(t_game *game, t_coord *coord)
{
	game->pos = malloc(sizeof(t_coord));
	if (!game->pos)
		return (1);
	game->pos->row = coord->row;
	game->pos->col = coord->col;
	return (0);
}

int	render_map(t_game *game)
{
	t_coord	coord;

	coord.row = 0;
	while (game->map[coord.row])
	{
		coord.col = 0;
		while (game->map[coord.row][coord.col])
		{
			if (game->map[coord.row][coord.col] == 'P')
				if (get_player_pos(game, &coord))
					return (1);
			if (game->map[coord.row][coord.col] != 'E')
				render_square(game, &coord, game->map[coord.row][coord.col]);
			else
				render_square(game, &coord, '0');
			coord.col++;
		}
		coord.row++;
	}
	render_score(game);
	return (0);
}

void	render_score(t_game *game)
{
	char	*moves;

	moves = ft_itoa(game->moves);
	if (!moves)
	{
		game->is_error = 1;
		close_window(game);
	}
	mlx_put_image_to_window(game->data->mlx_ptr, game->data->win_ptr,
		game->data->imgs->sign, IMG_SIZE / 2, IMG_SIZE / 5);
	mlx_string_put(game->data->mlx_ptr, game->data->win_ptr,
		IMG_SIZE - 5, IMG_SIZE / 2 + 5, 0xFFFFFF, moves);
	free(moves);
}
