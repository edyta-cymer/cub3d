/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:49:34 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/09 01:25:24 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void find_wall(t_data *data, t_ray *ray, t_vector2 *maps_cords)
{
	ray->door_hit = 0;
	ray->hit_door = 0;
	t_vector2 door_coords = {-1, -1};
	double door_dist = INFINITY;

	while (1)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			maps_cords->x += ray->step_x;
			ray->sideDistX += ray->del_dist_x;
			ray->side = 0;
		}
		else
		{
			maps_cords->y += ray->step_y;
			ray->sideDistY += ray->del_dist_y;
			ray->side = 1;
		}
		if (data->map[maps_cords->y][maps_cords->x] == '1')
			break;
		else if (data->map[maps_cords->y][maps_cords->x] == 'D' && !ray->door_hit)
		{
			ray->door_hit = 1;
			door_coords = (t_vector2){maps_cords->x, maps_cords->y};
			if (ray->side == 0)
				door_dist = ray->sideDistX - ray->del_dist_x / 2.0;
			else
				door_dist = ray->sideDistY - ray->del_dist_y / 2.0;
		}
	}
	double wall_dist;
	if (ray->side == 0)
		wall_dist = ray->sideDistX - ray->del_dist_x;
	else
		wall_dist = ray->sideDistY - ray->del_dist_y;
	if (ray->door_hit && door_dist < wall_dist)
	{
		ray->sideDistY -= ray->del_dist_y * 2;
		ray->hit_door = 1;
	}
	else
		ray->door_hit = 0;
}

int	init_txr_x(t_data *data, t_ray ray, float wallX)
{
	int		texture_x;

	if (ray.side == 0)
	{
		if (ray.ray_dir_x > 0)
			texture_x = (wallX * data->txr[2].txr_width);
		else
		{
			texture_x = (wallX * data->txr[3].txr_width);
			texture_x = data->txr[3].txr_width - texture_x - 1;
		}
	}
	else
	{
		if (ray.ray_dir_y > 0)
		{
			texture_x = (wallX * data->txr[1].txr_width);
			texture_x = data->txr[1].txr_width - texture_x - 1;
		}
		else
			texture_x = (wallX * data->txr[0].txr_width);
	}
	return (texture_x);
}

void	cast_rays(t_data *data)
{
	t_ray		ray;
	t_vector2	map_cords;
	int			x;
	float		camera_x;

	x = -1;
	while (++x < WIN_W)
	{
		camera_x = 2 * (x / (float)WIN_W) - 1;
		map_cords.x = (int)data->player.pos_x;
		map_cords.y = (int)data->player.pos_y;
		init_ray(data, &ray, map_cords, camera_x);
		find_wall(data, &ray, &map_cords);
		draw_wall(data, ray, x);
	}
}
