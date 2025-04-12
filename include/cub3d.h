/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:44:40 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/12 17:24:48 by ecymer           ###   ########.fr       */
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
# include <X11/extensions/Xfixes.h>
# include <sys/time.h>
# include <string.h>
# include <errno.h>

# ifndef M_PI
#  define M_PI 3.141592653
# endif

# define WIN_H 450
# define WIN_W 800
# define TILE_SIZE 64
# define FPS 90

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		txr_width;
	int		txr_height;
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
	t_image		image;
	int			txr_width;
	int			txr_height;
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

typedef	struct s_door
{
	t_vector2	coords;
	size_t		opened;
}	t_door;

typedef struct s_data
{
	t_textures	txr[6];
	char		**map;
	t_player	player;
	t_keys		keys;
	t_image		img;
	t_image		door;
	t_image		torch[6];
	void		*mlx;
	void		*window;
	int			proportions;
	int			mouse;
	size_t		last_frame;
	double		frameTime;
	int			current_anim;
	t_door		opened_doors[64];
}	t_data;

typedef struct s_bresenham
{
	t_vector2		current;
	t_vector2		delta;
	t_vector2		sign;
	int				error;
	int				error2;
	int				line_height;
	int				texture_id;
	int				color2;
	int				y_screen;
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
	float	wallDist;
	int		color;
	int		door_hit;
	int		door_side;
	int		texture_x;
	int		texture_y;
}	t_ray;

void			error(char *message, int type);
void			clean_up(t_data *data, int fd);
size_t			get_time(void);

int				ft_color_atoi(const char *nptr);
int				rgb_to_decimal(t_data *data, t_texture id_txr);
void			init_data(char *filepath, t_data *data);
void			ft_handle_colors(t_data *data, char **split_line, int fd, char *line);
int				add_path(t_data *data, char **split_line, int fd, char *line);
void			init_textures(t_data *data);

int				validate_map_format(char *str, char *ext);
void			validate_map(t_data *data);
void			validate_data(t_data *data, char *line, int fd);
void			create_map(t_data *data, char *line, int fd);
void			calc_proportions(t_data *data);

double			degree_to_radian(int degree);
void			ft_init_mlx(t_data *data);
void			mlx_put_txr(t_data *data, t_vector2 point1, t_vector2 point2, \
				t_ray ray);

void			cast_rays(t_data *data);
void			manage_keys(t_data *data);
int				manage_mouse(int x, int y, void *data);
void			my_mlx_pixel_put(t_image *data, int x, int y, int color);
void			mlx_put_torch(t_data *data, t_vector2 point1, t_vector2 point2);
int				check_texture_id(t_ray *ray, int texture_id);
unsigned int	get_pixel_color(t_image data, int x, int y);

void			draw_wall(t_data *data, t_ray ray, int x);
void			draw_texture(t_data *data, t_ray ray, t_vector2 point1, \
				t_vector2 point2);
int				init_txr_x(t_data *data, t_ray ray, float wallX);
void			init_ray(t_data *data, t_ray *ray, t_vector2 maps_cords, float camera_x);
void			count_ray_dir(t_ray *ray, t_data *data, float camera_x);
void			mlx_put_line(t_data *data, t_vector2 point1, t_vector2 point2, int clr);
void			draw_square(t_data *data, t_vector2 start_point, int color, int size);
void			draw_map(t_data *data, t_vector2 start_point);
void			init_torch(t_data *data);
void			mlx_put_torch(t_data *data, t_vector2 point1, t_vector2 point2);
void			init_bresenham(t_bresenham *b, t_vector2 point1, t_vector2 point2);
void			close_doors(t_data *data);
void			open_doors(t_data *data);
void			open_the_door(t_data *data, t_vector2 point1, int i);
void			draw_torch(t_data *data);
size_t			get_time(void);
int				get_torch_color(t_data *data, t_vector2 point1);
void			init_torch(t_data *data);
void	init_doors(t_data *data);
int	on_press(int keyhook, void *param);
int	on_release(int keyhook, void *param);
int	close_window(void *param);
int	*map_line_len(char **split_lines);
void	check_dir(t_data *data, char c);
void	count_frame_time(t_data *game_data, t_vector2 *point1);
void	init_img_addr(t_data *game_data);
void	handle_mlx(t_data *data);

#endif
