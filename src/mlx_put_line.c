/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:13:00 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/01 23:03:04 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_bresenham(t_bresenham *b, t_vector2 point1, t_vector2 point2)
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
	if (ray.color == -1)
	{
		ray.texture_y = (b->y_screen - point1.y) * \
		data->txr[b->texture_id].txr_height / b->line_height;
		b->color2 = get_pixel_color(data->txr[b->texture_id].image, \
		ray.texture_x, ray.texture_y);
		if (ray.side == 1)
			b->color2 /= 2;
	}
}

void	mlx_put_line(t_data *data, t_vector2 point1, t_vector2 point2, \
	t_ray ray)
{
	t_bresenham		b;

	b.line_height = WIN_H / ray.wallDist;
	init_bresenham(&b, point1, point2);
	b.y_screen = point1.y;
	b.color2 = ray.color;
	b.texture_id = 0;
	b.texture_id = check_texture_id(&ray, b.texture_id);
	while (1)
	{
		get_txr_color(&b, ray, data, point1);
		my_mlx_pixel_put(&data->img, point1.x, b.y_screen, b.color2);
		if (b.y_screen == point2.y)
			break ;
		b.error2 = b.error * 2;
		if (b.error2 < b.delta.x)
		{
			b.error += b.delta.x;
			b.y_screen += b.sign.y;
		}
	}
}
