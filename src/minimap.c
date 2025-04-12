/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:27:14 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/12 18:20:01 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_proportions(t_data *data)
{
	int	i;
	int	tmp;

	i = -1;
	data->proportions = 0;
	while (data->map[++i])
	{
		tmp = ft_strlen(data->map[i]);
		if (tmp > data->proportions)
			data->proportions = tmp;
	}
	if (i > data->proportions)
		data->proportions = i;
}

void	draw_square(t_data *data, t_vector2 start_point, int color, int size)
{
	t_vector2	end_point;
	int			i;

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

void	draw_player(t_data *data, t_vector2 start_point, int size, t_vector2 \
					saved_point)
{
	start_point.x = data->player.pos_x * size + saved_point.x;
	start_point.y = data->player.pos_y * size + saved_point.y - 1;
	draw_square(data, start_point, 0x00ff00, size / 2);
}

void	draw_map(t_data *data, t_vector2 start_point)
{
	t_vector2	saved_point;
	int			size;
	int			i;
	int			j;

	saved_point.x = start_point.x;
	saved_point.y = start_point.y;
	size = 200 / data->proportions;
	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == '1')
				draw_square(data, start_point, 0xffe600, size);
			else if (data->map[i][j] == 'D')
				draw_square(data, start_point, 0xff0000, size);
			start_point.x += size;
		}
		start_point.x = saved_point.x;
		start_point.y += size;
	}
	draw_player(data, start_point, size, saved_point);
}
