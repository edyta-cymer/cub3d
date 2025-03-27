/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:49:34 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/27 11:53:56 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_data *data, t_ray *ray, int *map_x, int *map_y)
{
	ray->ray_dir_x = cos(data->player.orientation);
	ray->ray_dir_y = sin(data->player.orientation);
	if (ray->ray_dir_x < 0)
		*map_x = (int)data->player.plane_x;
	else
		*map_x = (int)data->player.plane_x + 1;
	if (ray->ray_dir_y < 0)
		*map_y = (int)data->player.plane_y;
	else
		*map_y = (int)data->player.plane_y + 1;
	if (ray->ray_dir_x != 0)
		ray->del_ray_x = ((int)data->player.pos_x - data->player.pos_x) \
							/ ray->ray_dir_x;
	else
		ray->del_ray_x = INT32_MAX;
	if (ray->del_ray_y != 0)
		ray->del_ray_y = ((int)data->player.pos_y - data->player.pos_y) \
							/ ray->ray_dir_y;
	else
		ray->del_ray_y = INT32_MAX;
}

void	cast_rays(t_data *data)
{
	t_ray	ray;
	int		map_x;
	int		map_y;
}
