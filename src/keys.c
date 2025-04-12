/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:15:38 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/12 18:47:18 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (keyhook == XK_Escape)
	{
		clean_up(data, -1);
		exit(EXIT_SUCCESS);
	}
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
