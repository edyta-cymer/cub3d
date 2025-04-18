/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:13:00 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/12 19:11:18 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_bresenham(t_bresenham *b, t_vector2 point1, t_vector2 point2)
{
	b->delta.x = abs(point2.x - point1.x);
	b->delta.y = abs(point2.y - point1.y);
	if (point1.x < point2.x)
		b->sign.x = 1;
	else
		b->sign.x = -1;
	if (point1.y < point2.y)
		b->sign.y = 1;
	else
		b->sign.y = -1;
	b->error = b->delta.x - b->delta.y;
}

void	get_txr_color(t_bresenham *b, t_ray ray, t_data *data, t_vector2 point1)
{
	if (ray.color == -1 && b->texture_id < 4)
	{
		ray.texture_y = (b->y_screen - point1.y) * \
		data->txr[b->texture_id].txr_height / b->line_height;
		b->color2 = get_pixel_color(data->txr[b->texture_id].image, \
		ray.texture_x, ray.texture_y);
	}
	else if (b->texture_id == 4)
	{
		ray.texture_y = (b->y_screen - point1.y) * \
		data->door.txr_height / b->line_height;
		b->color2 = get_pixel_color(data->door, ray.texture_x, ray.texture_y);
	}
}

void	mlx_put_txr(t_data *data, t_vector2 point1, t_vector2 point2, \
	t_ray ray)
{
	t_bresenham		b;

	b.line_height = WIN_H / ray.wall_dist;
	init_bresenham(&b, point1, point2);
	b.y_screen = (point1.y > 0) * point1.y;
	b.color2 = ray.color;
	b.texture_id = 0;
	b.texture_id = check_texture_id(&ray, b.texture_id);
	while (1)
	{
		get_txr_color(&b, ray, data, point1);
		my_mlx_pixel_put(&data->img, point1.x, b.y_screen, b.color2);
		if (b.y_screen == point2.y || b.y_screen == WIN_H)
			break ;
		b.error2 = b.error * 2;
		if (b.error2 < b.delta.x)
		{
			b.error += b.delta.x;
			b.y_screen += b.sign.y;
		}
	}
}

void	mlx_put_line(t_data *data, t_vector2 point1, t_vector2 point2, int clr)
{
	t_bresenham		b;

	init_bresenham(&b, point1, point2);
	if (point1.y <= 0 && point2.y <= 0)
		return ;
	if (point1.y >= WIN_H && point2.y >= WIN_H)
		return ;
	while (1)
	{
		my_mlx_pixel_put(&data->img, point1.x, point1.y, clr);
		if (point1.y == point2.y)
			break ;
		b.error2 = b.error * 2;
		if (b.error2 < b.delta.x)
		{
			b.error += b.delta.x;
			point1.y += b.sign.y;
		}
	}
}
