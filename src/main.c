/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:44:39 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/28 18:56:31 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void manage_keys(t_data *data)
{
	float	dir_x;
	float	dir_y;

	if (data->keys.d)
	{
		data->player.orientation += degree_to_radian(1) * 0.5;
		if (data->player.orientation > 2 * M_PI)
			data->player.orientation -= 2 * M_PI;
		dir_x = cos(data->player.orientation);
		dir_y = sin(data->player.orientation);
		data->player.plane_x = -0.66 * dir_y;
		data->player.plane_y = 0.66 * dir_x;
	}
	if (data->keys.a)
	{
		data->player.orientation -= degree_to_radian(1) * 0.5;
		if (data->player.orientation < 0)
			data->player.orientation += 2 * M_PI;
		dir_x = cos(data->player.orientation);
		dir_y = sin(data->player.orientation);
		data->player.plane_x = -0.66 * dir_y;
		data->player.plane_y = 0.66 * dir_x;
	}
	if (data->keys.w)
	{
		if(data->map[(int)(data->player.pos_y + sin(data->player.orientation) * 0.3)][(int)(data->player.pos_x + cos(data->player.orientation) * 0.3)] != '1')
		{
			data->player.pos_x += cos(data->player.orientation) * 0.01;
			data->player.pos_y += sin(data->player.orientation) * 0.01;
		}
	}
	if (data->keys.s)
	{
		if(data->map[(int)(data->player.pos_y - sin(data->player.orientation) * 0.3)][(int)(data->player.pos_x - cos(data->player.orientation) * 0.3)] != '1')
		{
			data->player.pos_x -= cos(data->player.orientation) * 0.01;
			data->player.pos_y -= sin(data->player.orientation) * 0.01;
		}
	}
}

int	game_loop(void *data)
{
	t_data	*game_data;

	game_data = (t_data *)data;
	manage_keys(game_data);
	mlx_destroy_image(game_data->mlx, game_data->img.img);
	game_data->img.img = mlx_new_image(game_data->mlx, WIN_W, WIN_H);
	game_data->img.addr = mlx_get_data_addr(game_data->img.img, \
		&game_data->img.bits_per_pixel, &game_data->img.line_length, &game_data->img.endian);
	cast_rays(game_data);
	mlx_clear_window(game_data->mlx, game_data->window);
	mlx_put_image_to_window(game_data->mlx, game_data->window, game_data->img.img, 0, 0);
	return (0);
}

int on_press(int keyhook, void* param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keyhook == XK_w)
		data->keys.w = 1;
	if (keyhook == XK_a)	
		data->keys.a = 1;
	if (keyhook == XK_s)
		data->keys.s = 1;
	if (keyhook == XK_d)
		data->keys.d = 1;
	if (keyhook == XK_Escape)
	{
		clean_up(data, -1);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int on_release(int keyhook, void* param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keyhook == XK_w)
		data->keys.w = 0;
	if (keyhook == XK_a)	
		data->keys.a = 0;
	if (keyhook == XK_s)
		data->keys.s = 0;
	if (keyhook == XK_d)
		data->keys.d = 0;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		error("You can have only one argument", 0);
	init_data(argv[1], &data);
	ft_init_mlx(&data);
	mlx_hook(data.window, 2, 1L<<0, on_press, &data);
	mlx_hook(data.window, 3, 1L<<1, on_release, &data);
	mlx_loop_hook(data.mlx, &game_loop, &data);
	mlx_loop(data.mlx);
	clean_up(&data, -1);
	return (0);
}
