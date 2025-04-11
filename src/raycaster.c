/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:49:34 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/09 18:12:44 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void find_wall(t_data *data, t_ray *ray, t_vector2 *maps_cords)
{
	double door_dist = INFINITY;
	t_vector2 steps;

	steps.x = 0;
	steps.y = 0;
	while (1)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			maps_cords->x += ray->step_x;
			ray->sideDistX += ray->del_dist_x;
			ray->side = 0;
			steps.x++;
		}
		else
		{
			maps_cords->y += ray->step_y;
			ray->sideDistY += ray->del_dist_y;
			ray->side = 1;
			steps.y++;
		}
		if (data->map[maps_cords->y][maps_cords->x] == '1')
			break;
		else if (data->map[maps_cords->y][maps_cords->x] == 'D' && !ray->door_hit)
		{
			steps.x = 0;
			steps.y = 0;
			ray->door_hit = 1;
			ray->door_side = ray->side;
			if (ray->side == 0)
				door_dist = ray->sideDistX - ray->del_dist_x / 1.5;
			else
				door_dist = ray->sideDistY - ray->del_dist_y / 1.5;
		}
	}
	if (ray->side == 0)
		ray->wallDist = ray->sideDistX - ray->del_dist_x;
	else
		ray->wallDist = ray->sideDistY - ray->del_dist_y;
	if (ray->door_hit && door_dist < ray->wallDist)
	{
		ray->sideDistY -= ray->del_dist_y * steps.y;
		ray->sideDistX -= ray->del_dist_x * steps.x;
		ray->side = ray->door_side;
	}
	else
		ray->door_hit = 0;
}

int	init_txr_x(t_data *data, t_ray ray, float wallX)
{
	int		texture_x;

	if (ray.door_hit)
	{
		texture_x = (wallX * data->door.txr_width);
	}
	else if (ray.side == 0)
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
