/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:05:23 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/01 20:20:07 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	manage_d_a_keys(t_data *data, float dir_x, float dir_y)
{
	double	rotate_speed;

	rotate_speed = data->frameTime * 3.0;
	if (data->keys.d || data->mouse == 1)
	{
		data->player.orientation += rotate_speed;
		if (data->player.orientation > 2 * M_PI)
			data->player.orientation -= 2 * M_PI;
		data->player.plane_x = -0.66 * dir_y;
		data->player.plane_y = 0.66 * dir_x;
	}
	if (data->keys.a || data->mouse == -1)
	{
		data->player.orientation -= rotate_speed;
		if (data->player.orientation < 0)
			data->player.orientation += 2 * M_PI;
		data->player.plane_x = -0.66 * dir_y;
		data->player.plane_y = 0.66 * dir_x;
	}
}

void	manage_w_s_keys(t_data *data, float dir_x, float dir_y)
{
	double move_speed;

	move_speed = data->frameTime * 5.0;
	if (data->keys.w)
	{
		if (data->map[(int)(data->player.pos_y + dir_y * move_speed * 4)] \
		[(int)(data->player.pos_x + dir_x * move_speed * 4)] != '1')
		{
			data->player.pos_x += dir_x * move_speed;
			data->player.pos_y += dir_y * move_speed;
		}
	}
	if (data->keys.s)
	{
		if (data->map[(int)(data->player.pos_y - dir_y * move_speed * 4)] \
		[(int)(data->player.pos_x - dir_x * move_speed * 4)] != '1')
		{
			data->player.pos_x -= dir_x * move_speed;
			data->player.pos_y -= dir_y * move_speed;
		}
	}
}

void	manage_keys(t_data *data)
{
	float	dir_x;
	float	dir_y;

	dir_x = cos(data->player.orientation);
	dir_y = sin(data->player.orientation);
	manage_d_a_keys(data, dir_x, dir_y);
	manage_w_s_keys(data, dir_x, dir_y);
}

int	manage_mouse(int x, int y, void *data)
{
	t_data	*game_data;
	(void)y;

	game_data = (t_data *)data;
	if (x > WIN_W / 2)
		game_data->mouse = 1;
	else if (x < WIN_W / 2)
		game_data->mouse = -1;
	else
		game_data->mouse = 0;
	return (0);
}