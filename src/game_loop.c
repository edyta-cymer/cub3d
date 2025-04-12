/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:18:54 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/12 19:27:45 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(void *data)
{
	t_data		*game_data;
	t_vector2	point1;

	game_data = (t_data *)data;
	count_frame_time(game_data, &point1);
	manage_keys(game_data);
	mlx_destroy_image(game_data->mlx, game_data->img.img);
	init_img_addr(game_data);
	close_doors(game_data);
	cast_rays(game_data);
	draw_map(game_data, point1);
	draw_torch(game_data);
	mlx_clear_window(game_data->mlx, game_data->window);
	mlx_put_image_to_window(game_data->mlx, \
	game_data->window, game_data->img.img, 0, 0);
	game_data->last_frame = get_time();
	if (game_data->mouse != 0 && !game_data->keys.ctrl)
		mlx_mouse_move(game_data->mlx, game_data->window, WIN_W / 2, WIN_H / 2);
	game_data->mouse = 0;
	game_data->current_anim++;
	if (game_data->current_anim == 6)
		game_data->current_anim = 0;
	return (0);
}
