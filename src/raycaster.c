/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:49:34 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/01 00:54:50 by ecymer           ###   ########.fr       */
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
int	init_txr_x(t_data *data, t_ray ray, float wallX)
{
	int		texture_x;

	if (ray.side == 0)
	{
		if (ray.ray_dir_x < 0)
			texture_x = (wallX * data->txr[2].txr_width);
		else
		{
			texture_x = (wallX * data->txr[3].txr_width);
			texture_x = data->txr[3].txr_width - texture_x - 1;
		}
	}
	else
	{
		if (ray.ray_dir_y < 0)
		{
			texture_x = (wallX * data->txr[1].txr_width);
			texture_x = data->txr[1].txr_width - texture_x - 1;
		}
		else
			texture_x = (wallX * data->txr[0].txr_width);
	}
	return (texture_x);
}

void	draw_texture(t_data *data, t_ray ray, t_vector2 point1, t_vector2 point2)
{
	float	wallX;
	
	if (ray.side == 0)
		wallX = data->player.pos_y + ray.wallDist * ray.ray_dir_y;
	else 
		wallX = data->player.pos_x + ray.wallDist * ray.ray_dir_x;
	wallX -= floor(wallX);
	ray.texture_x = init_txr_x(data, ray, wallX);
	mlx_put_line(data, point1, point2, ray);
}

void	draw_wall(t_data *data, t_ray ray, int x)
{
	t_vector2	start_wall;
	t_vector2	end_wall;
	int			lineHeight;
	
	if (ray.side == 0)
		ray.wallDist = ray.sideDistX - ray.del_dist_x;
	else
		ray.wallDist = ray.sideDistY - ray.del_dist_y;
	lineHeight = WIN_H / ray.wallDist;
	start_wall.y = WIN_H / 2 - lineHeight / 2;
	start_wall.x = x;
	end_wall.y = WIN_H / 2 + lineHeight / 2;
	end_wall.x = x;
	ray.color = -1;
	draw_texture(data, ray, start_wall, end_wall);
	end_wall.y = 0;
	ray.color = rgb_to_decimal(data, C);
	mlx_put_line(data, start_wall, end_wall, ray);
	start_wall.y = WIN_H / 2 + lineHeight / 2;
	end_wall.y = WIN_H;
	ray.color = rgb_to_decimal(data, F);
	mlx_put_line(data, start_wall, end_wall, ray);
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

