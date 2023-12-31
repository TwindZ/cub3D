/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:00:29 by emlamoth          #+#    #+#             */
/*   Updated: 2023/10/15 11:21:25 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//----------define
# define WINWIDTH 1792
# define WINHEIGHT 1344
# define MINITILES 8
# define TEXTSIZE 
# define MOVESPEED 5
# define MOVE_SPEED 0.00007
# define ROTATE_SPEED 0.000040
# define MOUSE_SPEED 450
# define CHECKRADIUS 0.5
# define MINIHEIGHT 9
# define MINIWIDTH 15
# define MINISIZE 24

////////////----------error message
# define ERRARGC "Usage : ./cub3D <map.cub>\n"
# define ERRMAP	 "Invalid map file\n"
# define ERRIMG "Invalid image\n"
# define ERRCOLOR "Invalid color\n"
# define ERRPARSE "Informations are missing\n"
# define ERRPLAYER "Too many players\n"
# define ERRNOPLAYER "No player detected\n"
# define ERRCHAR "Wrong chars detected\n"
# define ERRWALL "The map isn't framed by wall\n"
# define ERRTEXT "Texture initialization failed\n"
# define ERRMAPINIT "Map initialization failed\n"
# define ERRMALLOC "Malloc Error\n"
# define ERRFORMAT "The file format isn't good\n"
# define ERRMLX "The inittialization failed\n"

//----------include
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include "../srcs/libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

//----------struct
typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	int				map_x;
	int				map_y;
	float			angle;
	int				start_map;
}			t_player;

typedef struct s_vect
{
	double			x;
	double			y;
}			t_vect;

typedef struct s_coor
{
	int	x;
	int	y;
}			t_coor;

typedef struct s_ray
{
	int				tex_x;
	int				line;
	t_vect			pos;
	t_vect			dir;
	t_vect			plane;
	double			cam_x;
	t_vect			ray_dir;
	t_vect			coord;
	t_vect			side_dist;
	t_vect			delta_dist;
	t_vect			step;
	int				side;
	double			perp_wall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			cam_angle;
	int32_t			mouse_x;
	int32_t			mouse_y;
}			t_ray;

typedef struct s_param
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	char			*door;
	uint32_t		wall;
	uint32_t		ceil;
	uint32_t		floor;
	int				flgfloor;
	int				flgceil;
	int				nbline;
	int				maxlen;
	int32_t			w_pos_x;
	int32_t			w_pos_y;
}			t_param;

typedef struct s_image
{
	mlx_image_t		*window;
	mlx_image_t		*minimap;
}			t_image;

typedef struct s_texture
{
	uint32_t		**north;
	uint32_t		**south;
	uint32_t		**east;
	uint32_t		**west;
	uint32_t		**door;
	int				door_flag;
	uint32_t		**ceil;
	uint32_t		**floor;
	mlx_texture_t	*north_tex;
	mlx_texture_t	*south_tex;
	mlx_texture_t	*east_tex;
	mlx_texture_t	*west_tex;
	mlx_texture_t	*door_tex;
	mlx_texture_t	*ceil_tex;
	mlx_texture_t	*floor_tex;
}			t_texture;

typedef struct s_data
{
	mlx_t			*mlx;
	t_param			param;
	t_texture		texture;
	t_image			image;
	t_player		player;
	t_ray			ray;
	double			angle;
	char			**map;
	int				view;
	int				y;
	int				x;
}			t_data;

//----------parsing
int			errhandler(char *msg);
void		parsing(t_data *data);
void		parse_map(t_data *data, int y);
void		wall_check(t_data *data);
char		*check_path(t_data *data, char *str);
void		color_decoder(t_data *data, char *str, uint32_t *surface);
void		set_dir(t_data *data, char c);
void		set_dir2(t_data *data, char c);
void		cub_exit(t_data *data, char *msg);
int			check_start_map(t_data *data);
int			player_position(t_data *data, int y, int x);
void		free_param(t_data *data);
//----------init
void		dup_map(t_data *data);
void		init_data(t_data *data);
void		init_map(t_data *data, char *path);
void		init_game(t_data *data);
uint32_t	ft_color(int32_t r, int32_t g, int32_t b, int32_t a);
void		loop(void *param);
void		init_game(t_data *data);
void		create_windows(t_data *data);
//----------init_text
void		free_text_ar(mlx_texture_t *texture, uint32_t **ar);
void		fill_array(mlx_texture_t *texture, uint32_t **ar);
uint32_t	**texture_to_array(mlx_texture_t *texture);
void		free_all_texture_array(t_data *data);
void		init_texture(t_data *data);
void		clean_texture(t_data *data);
//----------controls
void		key_binding(t_data *data);
void		rotate_vector(double *x, double *y, double angle);
void		move_player(t_data *data, double move_speed);
void		strafe_player(t_data *data, double strafe_speed);
//----------raycast
void		set_data(t_data *data, int x);
void		set_side_dist(t_data *data);
void		dda_calc(t_data *data);
void		dda(t_data *data);
void		set_draw_range(t_data *data);
void		find_hit(t_data *data, mlx_texture_t *texture);
void		drawline(t_data *data, mlx_texture_t *texture,
				uint32_t **arr, int x);
void		choose_texture(t_data *data, int x);
void		draw_vertline(t_data *data, int x);
void		track_window(t_data *data);
#endif
