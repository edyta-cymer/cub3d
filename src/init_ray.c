/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:45:08 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/12 19:07:19 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	count_ray_dir(t_ray *ray, t_data *data, float camera_x)
{
	ray->ray_dir_x = cos(data->player.orientation) + \
	data->player.plane_x * camera_x;
	ray->ray_dir_y = sin(data->player.orientation) + \
	data->player.plane_y * camera_x;
}

void	count_sidedist(t_ray *ray, t_data *data, t_vector2 maps_cords)
{
	if (ray->ray_dir_x < 0)
		ray->side_dist_x = (data->player.pos_x - maps_cords.x) * \
						ray->del_dist_x;
	else
		ray->side_dist_x = (maps_cords.x + 1 - data->player.pos_x) * \
						ray->del_dist_x;
	if (ray->ray_dir_y < 0)
		ray->side_dist_y = (data->player.pos_y - maps_cords.y) * \
						ray->del_dist_y;
	else
		ray->side_dist_y = (maps_cords.y + 1 - data->player.pos_y) * \
		ray->del_dist_y;
}

void	count_del_dist(t_ray *ray)
{
	if (ray->ray_dir_x != 0)
		ray->del_dist_x = fabs(1 / ray->ray_dir_x);
	else
		ray->del_dist_x = __FLT_MAX__;
	if (ray->ray_dir_y != 0)
		ray->del_dist_y = fabs(1 / ray->ray_dir_y);
	else
		ray->del_dist_y = __FLT_MAX__;
}

void	init_ray(t_data *data, t_ray *ray, t_vector2 maps_cords, float camera_x)
{
	count_ray_dir(ray, data, camera_x);
	ray->step_x = (ray->ray_dir_x > 0) - (ray->ray_dir_x < 0);
	ray->step_y = (ray->ray_dir_y > 0) - (ray->ray_dir_y < 0);
	ray->door_hit = 0;
	count_del_dist(ray);
	count_sidedist(ray, data, maps_cords);
}
