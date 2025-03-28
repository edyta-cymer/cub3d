/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:49:34 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/28 18:12:02 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_data *data, t_ray *ray, t_vector2 maps_cords, float camera_x)
{
	ray->ray_dir_x = cos(data->player.orientation) + data->player.plane_x * camera_x;
	ray->ray_dir_y = sin(data->player.orientation) + data->player.plane_y * camera_x;
	ray->step_x = (ray->ray_dir_x > 0) - (ray->ray_dir_x < 0);
	ray->step_y = (ray->ray_dir_y > 0) - (ray->ray_dir_y < 0);
	if (ray->ray_dir_x != 0)
		ray->del_dist_x = fabs(1 / ray->ray_dir_x);
	else
		ray->del_dist_x = __FLT_MAX__;
	if (ray->ray_dir_y != 0)
		ray->del_dist_y = fabs(1 / ray->ray_dir_y);
	else
		ray->del_dist_y = __FLT_MAX__;
	if (ray->ray_dir_x < 0)
		ray->sideDistX = (data->player.pos_x - maps_cords.x) * \
						ray->del_dist_x;
	else
		ray->sideDistX = (maps_cords.x + 1 - data->player.pos_x) * \
						ray->del_dist_x;
	if (ray->ray_dir_y < 0)
		ray->sideDistY = (data->player.pos_y - maps_cords.y) * \
						ray->del_dist_y;
	else
		ray->sideDistY = (maps_cords.y + 1 - data->player.pos_y) * \
						ray->del_dist_y;
}
void	find_wall(t_data *data, t_ray *ray, t_vector2 *maps_cords)
{
	while (1)
	{
		if (data->map[maps_cords->y][maps_cords->x] == '1')
			break ;
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
	}
}

void	draw_wall(t_data *data, t_ray ray, int x)
{
	t_vector2	start_wall;
	t_vector2	end_wall;
	float		wallDist;
	int			lineHeight;
	int			color;
	
	if (ray.side == 0)
		wallDist = ray.sideDistX - ray.del_dist_x;
	else
		wallDist = ray.sideDistY - ray.del_dist_y;
	lineHeight = WIN_H / wallDist;
	start_wall.y = WIN_H / 2 - lineHeight / 2;
	start_wall.x = x;
	end_wall.y = WIN_H / 2 + lineHeight / 2;
	end_wall.x = x;
	color = (ray.side == 0) * 0x00FFFF00 + (ray.side == 1) * 0x00FFFF00 / 2; 
	mlx_put_line(data, start_wall, end_wall, color);
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

