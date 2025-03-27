/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:33:16 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/27 07:38:10 by kkonarze         ###   ########.fr       */
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

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	mlx_put_line(t_data *data, t_vector2 point1, t_vector2 point2)
{
	t_bresenham	b;

	init_bresenham(&b, point1, point2);
	while (1)
	{
		my_mlx_pixel_put(&data->img, point1.x, point1.y, 0x00FFFF00);
		if (point1.x == point2.x && point1.y == point2.y)
			break ;
		b.error2 = b.error * 2;
		if (b.error2 > -b.delta.y)
		{
			b.error -= b.delta.y;
			point1.x += b.sign.x;
		}
		if (b.error2 < b.delta.x)
		{
			b.error += b.delta.x;
			point1.y += b.sign.y;
		}
	}
}

void	ft_init_mlx(t_data *data)
{
	int	x;

	data->mlx = mlx_init();
	if (!data->mlx)
		return (clean_up(data, -1), error("Problem with mlx connection.", 0));
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
	mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
}
