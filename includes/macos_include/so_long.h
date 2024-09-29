/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:49:03 by mrochedy          #+#    #+#             */
/*   Updated: 2024/09/29 17:05:43 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "ft_printf.h"
# include "get_next_line.h"

# define VALID_CHARS "01CEPe"
# define IMG_SIZE 64
# define ESC_KEY 53
# define W_KEY 13
# define A_KEY 0
# define D_KEY 2
# define S_KEY 1
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define DOWN_ARROW 125
# define UP_ARROW 126
# define KEYPRESS 2
# define KEYPRESSMASK 3
# define DESTROYNOTIFY 17
# define STRUCTURENOTIFYMASK 0

// THIS PART ISN'T NORMED ACCORDING TO THE 42 NORMINETTE
// BUT IS NECESSARY TO MAKE IT CROSS-COMPATIBLE
# define DESTROY_DISPLAY(mlx_ptr)

typedef struct s_imgs
{
	void	*ground;
	void	*wall;
	void	*collectible;
	void	*player;
	void	*exit;
	void	*enemy;
	void	*sign;
}	t_imgs;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_imgs	*imgs;
}	t_data;

typedef struct s_coord
{
	int	row;
	int	col;
}	t_coord;

typedef struct s_game
{
	char	**map;
	int		eaten;
	int		moves;
	int		collectibles;
	int		is_error;
	t_data	*data;
	t_coord	*pos;
}	t_game;

int		remove_nl(char **str);
int		check_basic_errors(int argc, char **argv);
int		check_map_errors(t_game *game);
void	free_map(char ***map, int size);
void	safe_free(void *ptr);
int		check_valid_path(char **map);
int		manage_window(t_game *game);
int		init_images(t_game *game);
int		render_map(t_game *game);
void	render_square(t_game *game, t_coord *coord, char type);
void	render_exit(t_game *game);
void	render_score(t_game *game);
int		close_window(t_game *game);
void	move_player(t_game *game, t_coord *old, int new_row, int new_col);
char	*ft_itoa(int n);

#endif
