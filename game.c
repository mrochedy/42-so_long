/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:54:43 by mrochedy          #+#    #+#             */
/*   Updated: 2024/07/01 10:46:24 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_and_close(t_game *game, char *text)
{
	ft_printf(text);
	close_window(game);
}

void	move_player(t_game *game, t_coord *old, int new_row, int new_col)
{
	if (game->map[new_row][new_col] != '1')
	{
		render_square(game, game->pos, '0');
		game->pos->row = new_row;
		game->pos->col = new_col;
		render_square(game, game->pos, 'P');
		if (game->map[new_row][new_col] == 'C')
			(game->eaten)++;
		if (game->map[new_row][new_col] == 'E' &&
			game->eaten == game->collectibles)
			print_and_close(game, "YOU WIN\n");
		if (game->map[new_row][new_col] == 'e')
			print_and_close(game, "GAME OVER\n");
		if (game->map[old->row][old->col] != 'E')
			game->map[old->row][old->col] = '0';
		(game->moves)++;
		if (game->eaten == game->collectibles)
			render_exit(game);
		render_score(game);
	}
}
