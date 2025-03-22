/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:33:16 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/22 19:58:15 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_init_mlx(t_data *data)
{
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
		return (clean_up(data, -1), error("Problem with mlx_get_data_addr", 0));
}

