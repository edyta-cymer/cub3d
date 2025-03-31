/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:33:16 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/01 00:54:58 by ecymer           ###   ########.fr       */
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

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > WIN_W || y < 0 || y > WIN_H)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_pixel_color(t_image data, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= 64 || y < 0 || y >= 64)
		return (0);
	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	mlx_put_line(t_data *data, t_vector2 point1, t_vector2 point2, \
	t_ray ray)
{
	t_bresenham	b;
	int			y_screen;
	int			line_height;
	int			texture_y;
	int			texture_id;
	unsigned int color2;
	
	line_height = WIN_H / ray.wallDist;
	init_bresenham(&b, point1, point2);
	y_screen = point1.y;
	color2 = ray.color;
	if (ray.side == 0)
	{
		if (ray.ray_dir_x < 0)
			texture_id = 2;
		else
			texture_id = 3;
	}
	else
	{
		if (ray.ray_dir_y < 0)
			texture_id = 1;
		else
			texture_id = 0;
	}
	while (1)
	{
		if (ray.color == -1)
		{
			texture_y = (y_screen - point1.y) * data->txr[texture_id].txr_height / line_height;
			color2 = get_pixel_color(data->txr[texture_id].image, ray.texture_x, texture_y);
			if (ray.side == 1)
				color2 /= 2;
		}
		my_mlx_pixel_put(&data->img, point1.x, y_screen, color2);
		if (y_screen == point2.y)
			break ;
		b.error2 = b.error * 2;
		if (b.error2 < b.delta.x)
		{
			b.error += b.delta.x;
			y_screen += b.sign.y;
		}
	}
}

void	ft_init_mlx(t_data *data)
{
	data->window = mlx_new_window(data->mlx, WIN_W, WIN_H, "pawel Jumper");
	if (!data->window)
		return (clean_up(data, -1), error("Problem with mlx_new_window", 0));
	data->img.img = mlx_new_image(data->mlx, WIN_W, WIN_H);
	if (!data->img.img)
		return (clean_up(data, -1), error("Problem with mlx_new_image", 0));
	data->img.addr = mlx_get_data_addr(data->img.img, \
	&data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	if (!data->img.addr)
		return (clean_up(data, -1), error("Problem with mlx_get_data_adr", 0));
}
