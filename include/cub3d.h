/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:44:40 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/10 19:27:00 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

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

typedef struct	s_data {
	t_textures	txr[6];
	char		**map;
}	t_data;

void	error(char *message, int type);
void	clean_up(t_data *data, int fd);
int		ft_color_atoi(const char *nptr);
void	init_data(char *filepath, t_data *data);
void	ft_handle_colors(t_data *data, char **split_line, int fd, char *line);
int		validate_map_format(char *str, char *ext);
void	validate_data(t_data *data, char *line, int fd);
#endif


