/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:15:38 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/12 19:36:05 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	change_mouse_state(t_data *data)
{
	if (data->keys.ctrl)
		mlx_mouse_show(data->mlx, data->window);
	else
		mlx_mouse_hide(data->mlx, data->window);
}

int	on_press(int keyhook, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keyhook == XK_w)
		data->keys.w = 1;
	if (keyhook == XK_a)
		data->keys.a = 1;
	if (keyhook == XK_s)
		data->keys.s = 1;
	if (keyhook == XK_d)
		data->keys.d = 1;
	if (keyhook == XK_Left)
		data->keys.l = 1;
	if (keyhook == XK_Right)
		data->keys.r = 1;
	if (keyhook == XK_Control_L)
	{
		data->keys.ctrl = !data->keys.ctrl;
		change_mouse_state(data);
	}
	if (keyhook == XK_Escape)
		return (clean_up(data, -1), exit(EXIT_SUCCESS), 0);
	if (keyhook == XK_space)
		open_doors(data);
	return (0);
}

int	on_release(int keyhook, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keyhook == XK_w)
		data->keys.w = 0;
	if (keyhook == XK_a)
		data->keys.a = 0;
	if (keyhook == XK_s)
		data->keys.s = 0;
	if (keyhook == XK_d)
		data->keys.d = 0;
	if (keyhook == XK_Left)
		data->keys.l = 0;
	if (keyhook == XK_Right)
		data->keys.r = 0;
	return (0);
}
