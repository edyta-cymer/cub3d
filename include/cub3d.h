/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:44:40 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/28 18:08:43 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include <X11/keysym.h>

# ifndef M_PI
#  define M_PI 3.141592653
# endif

# define WIN_H 900
# define WIN_W 1600
# define TILE_SIZE 64

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef enum id_texture
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
}				t_texture;

typedef struct s_textures
{
	t_texture	id_txr;
	char		*path;
	int			rgb_letter[3];
}	t_textures;

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	double	orientation;
	double	plane_x;
	double	plane_y;
}				t_player;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
}				t_keys;

typedef struct s_vector2
{
	int	x;
	int	y;
}				t_vector2;

typedef struct s_data
{
	t_textures	txr[6];
	char		**map;
	t_player	player;
	t_keys		keys;
	t_image		img;
	void		*mlx;
	void		*window;
}	t_data;

typedef struct s_bresenham
{
	t_vector2	current;
	t_vector2	delta;
	t_vector2	sign;
	int			error;
	int			error2;
}	t_bresenham;

typedef struct s_ray
{
	float	ray_dir_x;
	float	ray_dir_y;
	float	del_dist_x;
	float	del_dist_y;
	int		step_x;
	int		step_y;
	float	sideDistX;
	float	sideDistY;
	int		side;
}	t_ray;


void	error(char *message, int type);
void	clean_up(t_data *data, int fd);

int		ft_color_atoi(const char *nptr);
void	init_data(char *filepath, t_data *data);
void	ft_handle_colors(t_data *data, char **split_line, int fd, char *line);

int		validate_map_format(char *str, char *ext);
void	validate_map(t_data *data);
void	validate_data(t_data *data, char *line, int fd);
void	create_map(t_data *data, char *line, int fd);

double	degree_to_radian(int degree);
void	ft_init_mlx(t_data *data);
void	mlx_put_line(t_data *data, t_vector2 point1, t_vector2 point2, int color);

void	cast_rays(t_data *data);

#endif
