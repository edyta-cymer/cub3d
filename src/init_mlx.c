/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:33:16 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/12 19:05:43 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	check_texture_id(t_ray *ray, int texture_id)
{
	if (ray->door_hit)
		texture_id = 4;
	else if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			texture_id = 2;
		else
			texture_id = 3;
	}
	else
	{
		if (ray->ray_dir_y < 0)
			texture_id = 0;
		else
			texture_id = 1;
	}
	return (texture_id);
}

void	ft_init_mlx(t_data *data)
{
	data->window = NULL;
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
	data->last_frame = get_time();
	data->frame_time = 0;
	data->mouse = 0;
	data->current_anim = 0;
	mlx_mouse_hide(data->mlx, data->window);
	mlx_mouse_move(data->mlx, data->window, WIN_W / 2, WIN_H / 2);
}

void	handle_mlx(t_data *data)
{
	ft_init_mlx(data);
	mlx_hook(data->window, 2, 1L << 0, on_press, data);
	mlx_hook(data->window, 3, 1L << 1, on_release, data);
	mlx_hook(data->window, 17, 0, close_window, data);
	mlx_hook(data->window, 6, 1L << 6, manage_mouse, data);
	mlx_loop_hook(data->mlx, &game_loop, data);
	mlx_loop(data->mlx);
}
