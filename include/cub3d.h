/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:44:40 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/18 18:44:50 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

# ifndef M_PI
#  define M_PI 3.141592653
# endif


typedef enum id_texture
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
} t_texture;

typedef struct	s_textures {
	t_texture	id_txr;
	char		*path;
	int			rgb_letter[3];
}	t_textures;

typedef struct s_player {
	float pos_x;
	float pos_y;
	double	orientation;
} t_player;

typedef struct s_vector2 {
	int x;
	int y;
} t_vector2;

typedef struct	s_data {
	t_textures	txr[6];
	char		**map;
	t_player	t_player;
}	t_data;



void	error(char *message, int type);
void	clean_up(t_data *data, int fd);
int		ft_color_atoi(const char *nptr);
void	init_data(char *filepath, t_data *data);
void	ft_handle_colors(t_data *data, char **split_line, int fd, char *line);
int		validate_map_format(char *str, char *ext);
void	validate_data(t_data *data, char *line, int fd);
void	create_map(t_data *data, char *line, int fd);
double	degree_to_radian(int degree);
#endif


