/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:05:23 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/30 17:12:36 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	manage_keys(t_data *data)
{
	float	dir_x;
	float	dir_y;

	dir_x = cos(data->player.orientation);
	dir_y = sin(data->player.orientation);
	if (data->keys.d)
	{
		data->player.orientation += degree_to_radian(1) * 0.5;
		if (data->player.orientation > 2 * M_PI)
			data->player.orientation -= 2 * M_PI;
		data->player.plane_x = -0.66 * dir_y;
		data->player.plane_y = 0.66 * dir_x;
	}
	if (data->keys.a)
	{
		data->player.orientation -= degree_to_radian(1) * 0.5;
		if (data->player.orientation < 0)
			data->player.orientation += 2 * M_PI;
		data->player.plane_x = -0.66 * dir_y;
		data->player.plane_y = 0.66 * dir_x;
	}
	if (data->keys.w)
	{
		if (data->map[(int)(data->player.pos_y + dir_y * 0.3)] \
		[(int)(data->player.pos_x + dir_x * 0.3)] != '1')
		{
			data->player.pos_x += dir_x * 0.01;
			data->player.pos_y += dir_y * 0.01;
		}
	}
	if (data->keys.s)
	{
		if (data->map[(int)(data->player.pos_y - dir_y * 0.3)] \
		[(int)(data->player.pos_x - dir_x * 0.3)] != '1')
		{
			data->player.pos_x -= dir_x * 0.01;
			data->player.pos_y -= dir_y * 0.01;
		}
	}
}