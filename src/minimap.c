/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:27:14 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/02 20:47:27 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_data *data, t_vector2 start_point, int color, int size)
{
	t_vector2	end_point;
	int	i;

	i = -1;
	
	end_point.y = start_point.y + size;
	end_point.x = start_point.x;
	while (++i < size)
	{
		mlx_put_line(data, start_point, end_point, color);
		start_point.x++;
		end_point.x++;
	}
	
}


