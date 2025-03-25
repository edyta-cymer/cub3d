/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:49:34 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/25 20:04:09 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_rays(t_data *data)
{
	float	ray_dir_x;
	float	ray_dir_y;
	float	delta_ray_x;
	float	delta_ray_y;

	ray_dir_x = cos(data->player.orientation);
	ray_dir_y = sin(data->player.orientation);
	delta_ray_x = (int)data->player.pos_x - data->player.pos_x / ray_dir_x;
}