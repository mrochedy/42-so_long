/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:28:05 by mrochedy          #+#    #+#             */
/*   Updated: 2024/09/28 16:49:20 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_images(t_game *game)
{
	int		a;
	t_imgs	*imgs;

	game->data->imgs = malloc(sizeof(t_imgs));
	if (!game->data->imgs)
		return (game->data->imgs = NULL, 1);
	imgs = game->data->imgs;
	imgs->ground = mlx_xpm_file_to_image(game->data->mlx_ptr,
			"assets/ground.xpm", &a, &a);
	imgs->wall = mlx_xpm_file_to_image(game->data->mlx_ptr,
			"assets/wall.xpm", &a, &a);
	imgs->collectible = mlx_xpm_file_to_image(game->data->mlx_ptr,
			"assets/collectible.xpm", &a, &a);
	imgs->player = mlx_xpm_file_to_image(game->data->mlx_ptr,
			"assets/player.xpm", &a, &a);
	imgs->exit = mlx_xpm_file_to_image(game->data->mlx_ptr,
			"assets/exit.xpm", &a, &a);
	imgs->enemy = mlx_xpm_file_to_image(game->data->mlx_ptr,
			"assets/enemy.xpm", &a, &a);
	imgs->sign = mlx_xpm_file_to_image(game->data->mlx_ptr,
			"assets/sign.xpm", &a, &a);
	if (!imgs->ground || !imgs->wall || !imgs->collectible || !imgs->player
		|| !imgs->exit || !imgs->enemy || !game->data->imgs->sign)
		close_window(game);
	return (0);
}

int	close_window(t_game *game)
{
	if (game->data->imgs->ground)
		mlx_destroy_image(game->data->mlx_ptr, game->data->imgs->ground);
	if (game->data->imgs->wall)
		mlx_destroy_image(game->data->mlx_ptr, game->data->imgs->wall);
	if (game->data->imgs->collectible)
		mlx_destroy_image(game->data->mlx_ptr, game->data->imgs->collectible);
	if (game->data->imgs->player)
		mlx_destroy_image(game->data->mlx_ptr, game->data->imgs->player);
	if (game->data->imgs->exit)
		mlx_destroy_image(game->data->mlx_ptr, game->data->imgs->exit);
	if (game->data->imgs->enemy)
		mlx_destroy_image(game->data->mlx_ptr, game->data->imgs->enemy);
	if (game->data->imgs->sign)
		mlx_destroy_image(game->data->mlx_ptr, game->data->imgs->sign);
	if (game->data->mlx_ptr && game->data->win_ptr)
		mlx_destroy_window(game->data->mlx_ptr, game->data->win_ptr);
	if (game->data->mlx_ptr)
	{
		DESTROY_DISPLAY(game->data->mlx_ptr);
		free(game->data->mlx_ptr);
	}
	free(game->data->imgs);
	if (game->pos)
		free(game->pos);
	return (free_map(&game->map, 0), free(game->data), exit(game->is_error), 0);
}

static int	handle_input(int keysym, t_game *game)
{
	t_coord	old_coord;

	old_coord.row = game->pos->row;
	old_coord.col = game->pos->col;
	if (keysym == ESC_KEY)
		close_window(game);
	else if (keysym == w_KEY || keysym == W_KEY || keysym == TOP_ARROW)
		move_player(game, &old_coord, old_coord.row - 1, old_coord.col);
	else if (keysym == a_KEY || keysym == A_KEY || keysym == LEFT_ARROW)
		move_player(game, &old_coord, old_coord.row, old_coord.col - 1);
	else if (keysym == d_KEY || keysym == D_KEY || keysym == RIGHT_ARROW)
		move_player(game, &old_coord, old_coord.row, old_coord.col + 1);
	else if (keysym == s_KEY || keysym == S_KEY || keysym == DOWN_ARROW)
		move_player(game, &old_coord, old_coord.row + 1, old_coord.col);
	return (0);
}

int	manage_window(t_game *game)
{
	if (init_images(game))
		return (1);
	if (render_map(game))
		return (1);
	mlx_hook(game->data->win_ptr, DESTROYNOTIFY,
		STRUCTURENOTIFYMASK, &close_window, game);
	mlx_hook(game->data->win_ptr, KEYPRESS, KEYPRESSMASK,
		&handle_input, game);
	mlx_loop(game->data->mlx_ptr);
	return (0);
}
