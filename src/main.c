/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:44:39 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/12 18:02:21 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	clean_up(data, -1);
	exit(EXIT_SUCCESS);
}

void	count_frame_time(t_data *game_data, t_vector2 *point1)
{
	while (get_time() - game_data->last_frame < 1000 / FPS)
		;
	game_data->frameTime = (get_time() - game_data->last_frame) / 1000.0;
	point1->x = 10;
	point1->y = 10;
}

void	init_img_addr(t_data *game_data)
{
	game_data->img.img = mlx_new_image(game_data->mlx, WIN_W, WIN_H);
	game_data->img.addr = mlx_get_data_addr(game_data->img.img, \
		&game_data->img.bits_per_pixel, \
		&game_data->img.line_length, &game_data->img.endian);
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
	handle_mlx(&data);
	clean_up(&data, -1);
	return (0);
}
