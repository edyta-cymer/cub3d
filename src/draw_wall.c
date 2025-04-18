/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:36:20 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/12 19:10:03 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_texture(t_data *data, t_ray ray, t_vector2 point1, \
	t_vector2 point2)
{
	float	wall_x;

	if (ray.side == 0)
		wall_x = data->player.pos_y + ray.wall_dist * ray.ray_dir_y;
	else
		wall_x = data->player.pos_x + ray.wall_dist * ray.ray_dir_x;
	wall_x -= floor(wall_x);
	ray.texture_x = init_txr_x(data, ray, wall_x);
	mlx_put_txr(data, point1, point2, ray);
}

float	count_wall_dist(t_ray ray)
{
	if (ray.door_hit)
	{
		if (ray.side == 0)
			ray.wall_dist = (ray.side_dist_x - ray.del_dist_x / 1.5);
		else
			ray.wall_dist = (ray.side_dist_y - ray.del_dist_y / 1.5);
	}
	else
	{
		if (ray.side == 0)
			ray.wall_dist = ray.side_dist_x - ray.del_dist_x;
		else
			ray.wall_dist = ray.side_dist_y - ray.del_dist_y;
	}
	return (ray.wall_dist);
}

void	draw_wall(t_data *data, t_ray ray, int x)
{
	t_vector2	start_wall;
	t_vector2	end_wall;
	int			line_height;

	ray.wall_dist = count_wall_dist(ray);
	line_height = WIN_H / ray.wall_dist;
	start_wall.y = WIN_H / 2 - line_height / 2;
	start_wall.x = x;
	end_wall.y = WIN_H / 2 + line_height / 2;
	end_wall.x = x;
	ray.color = -1;
	draw_texture(data, ray, start_wall, end_wall);
	end_wall.y = 0;
	ray.color = rgb_to_decimal(data, C);
	mlx_put_line(data, start_wall, end_wall, ray.color);
	start_wall.y = WIN_H / 2 + line_height / 2;
	end_wall.y = WIN_H;
	ray.color = rgb_to_decimal(data, F);
	mlx_put_line(data, start_wall, end_wall, ray.color);
}
