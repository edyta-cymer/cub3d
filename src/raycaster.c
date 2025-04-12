/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:49:34 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/12 19:11:40 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_door(t_ray *ray, t_vector2 steps, double door_dist)
{
	if (ray->side == 0)
		ray->wall_dist = ray->side_dist_x - ray->del_dist_x;
	else
		ray->wall_dist = ray->side_dist_y - ray->del_dist_y;
	if (ray->door_hit && door_dist < ray->wall_dist)
	{
		ray->side_dist_y -= ray->del_dist_y * steps.y;
		ray->side_dist_x -= ray->del_dist_x * steps.x;
		ray->side = ray->door_side;
	}
	else
		ray->door_hit = 0;
}

void	check_next_block(t_ray *ray, t_vector2 *maps_cords, t_vector2 *steps)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		maps_cords->x += ray->step_x;
		ray->side_dist_x += ray->del_dist_x;
		ray->side = 0;
		steps->x++;
	}
	else
	{
		maps_cords->y += ray->step_y;
		ray->side_dist_y += ray->del_dist_y;
		ray->side = 1;
		steps->y++;
	}
}

void	find_wall(t_data *data, t_ray *ray, t_vector2 *maps_cords)
{
	double		door_dist;
	t_vector2	steps;

	door_dist = INFINITY;
	steps.x = 0;
	steps.y = 0;
	while (1)
	{
		check_next_block(ray, maps_cords, &steps);
		if (data->map[maps_cords->y][maps_cords->x] == '1')
			break ;
		else if (data->map[maps_cords->y][maps_cords->x] == 'D' \
		&& !ray->door_hit)
		{
			steps.x = 0;
			steps.y = 0;
			ray->door_hit = 1;
			ray->door_side = ray->side;
			if (ray->side == 0)
				door_dist = ray->side_dist_x - ray->del_dist_x / 1.5;
			else
				door_dist = ray->side_dist_y - ray->del_dist_y / 1.5;
		}
	}
	check_door(ray, steps, door_dist);
}

int	init_txr_x(t_data *data, t_ray ray, float wallX)
{
	int		texture_x;

	if (ray.door_hit)
		texture_x = (wallX * data->door.txr_width);
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
