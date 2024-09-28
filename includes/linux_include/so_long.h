/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:49:03 by mrochedy          #+#    #+#             */
/*   Updated: 2024/09/28 14:49:46 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "ft_printf.h"
# include "get_next_line.h"

# define VALID_CHARS "01CEPe"
# define IMG_SIZE 64
# define ESC_KEY XK_Escape
# define w_KEY XK_w
# define W_KEY XK_W
# define a_KEY XK_a
# define A_KEY XK_A
# define d_KEY XK_d
# define D_KEY XK_D
# define s_KEY XK_s
# define S_KEY XK_S
# define LEFT_ARROW
# define RIGHT_ARROW
# define DOWN_ARROW
# define TOP_ARROW
# define KEYPRESS KeyPress
# define KEYPRESSMASK KeyPressMask
# define DESTROYNOTIFY DestroyNotify
# define STRUCTURENOTIFYMASK StructureNotifyMask
# define DESTROY_DISPLAY(mlx_ptr) mlx_destroy_display(mlx_ptr)

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

typedef struct s_coord {
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
