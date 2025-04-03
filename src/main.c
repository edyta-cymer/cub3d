/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:44:39 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/02 22:51:47 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (size_t)1000) + (tv.tv_usec / 1000));
}

int	game_loop(void *data)
{
	t_data	*game_data;
	t_vector2 point1;

	game_data = (t_data *)data;
	while(get_time() - game_data->last_frame < 1000 / FPS)
		;
	game_data->frameTime = (get_time() - game_data->last_frame) / 1000.0;
	point1.x = 10;
	point1.y = 10;
	manage_keys(game_data);
	mlx_destroy_image(game_data->mlx, game_data->img.img);
	game_data->img.img = mlx_new_image(game_data->mlx, WIN_W, WIN_H);
	game_data->img.addr = mlx_get_data_addr(game_data->img.img, \
		&game_data->img.bits_per_pixel, \
		&game_data->img.line_length, &game_data->img.endian);
	cast_rays(game_data);
	draw_map(game_data, point1);
	mlx_clear_window(game_data->mlx, game_data->window);
	mlx_put_image_to_window(game_data->mlx, \
	game_data->window, game_data->img.img, 0, 0);
	game_data->last_frame = get_time();
	if (game_data->mouse != 0)
		mlx_mouse_move(game_data->mlx, game_data->window, WIN_W / 2, WIN_H / 2);
	game_data->mouse = 0;
	return (0);
}

int	on_press(int keyhook, void *param)
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

int	on_release(int keyhook, void *param)
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

int	close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	clean_up(data, -1);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		error("You can have only one argument", 0);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (clean_up(&data, -1), \
		error("Problem with mlx connection.", 0), 0);
	init_data(argv[1], &data);
	ft_init_mlx(&data);
	mlx_hook(data.window, 2, 1L << 0, on_press, &data);
	mlx_hook(data.window, 3, 1L << 1, on_release, &data);
	mlx_hook(data.window, 17, 0, close_window, &data);
	mlx_hook(data.window, 6, 1L << 6, manage_mouse, &data);
	mlx_loop_hook(data.mlx, &game_loop, &data);
	mlx_loop(data.mlx);
	clean_up(&data, -1);
	return (0);
}
