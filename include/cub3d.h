/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:44:40 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/06 19:02:11 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H

# define CUB3D_H

#include "libft.h"
#include <fcntl.h>

void	error_handling(char *message, int type);

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
	t_texture	id_texture;
	char		*path;
	int			colors_letter[3];
}	t_textures;

typedef struct	s_data {
	struct		textures;
	char		**map;
}	t_data;

#endif


