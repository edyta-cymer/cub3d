/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:22:39 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/12 17:14:44 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_torch(t_data *data)
{
	t_vector2	point;
	t_vector2	point2;
	float		x;

	point.y = WIN_H - 1;
	point.x = WIN_W / 3 * 2;
	point2.y = WIN_H - (data->torch[data->current_anim].txr_height * 4) - 1;
	point2.x = WIN_W / 3 * 2;
	x = 0;
	while (x <= (float)data->torch[data->current_anim].txr_width)
	{
		mlx_put_torch(data, point, point2);
		x += 0.25;
		point2.x++;
		point.x++;
	}
}

int	get_torch_color(t_data *data, t_vector2 point1)
{
	int	color;

	color = get_pixel_color(data->torch[data->current_anim], \
	point1.x, point1.y);
	return (color);
}

void	mlx_put_torch(t_data *data, t_vector2 point1, t_vector2 point2)
{
	t_bresenham		b;
	t_vector2		current_point;
	int				color;
	float			y;

	init_bresenham(&b, point1, point2);
	b.y_screen = (point1.y > 0) * point1.y;
	current_point.x = (point1.x - WIN_W / 3 * 2) / 4;
	y = 50;
	while (1)
	{
		current_point.y = (int)y;
		color = get_torch_color(data, current_point);
		if (color > 0)
			my_mlx_pixel_put(&data->img, point1.x, b.y_screen, color);
		if (b.y_screen == point2.y || b.y_screen == WIN_H || y == 0)
			break ;
		b.error2 = b.error * 2;
		if (b.error2 < b.delta.x)
		{
			b.error += b.delta.x;
			b.y_screen += b.sign.y;
			y -= 0.25;
		}
	}
}

void	init_torch(t_data *data)
{
	int		i;
	char	*path;
	char	*tmp;
	char	*tmp2;

	i = -1;
	while (++i < 6)
	{
		tmp = ft_itoa(i);
		path = ft_strjoin("./torch/frame", tmp);
		free(tmp);
		tmp2 = ft_strjoin(path, ".xpm");
		free(path);
		data->torch[i].txr_height = 64;
		data->torch[i].txr_width = 64;
		data->torch[i].img = mlx_xpm_file_to_image(data->mlx, \
		tmp2, &data->torch[i].txr_width, &data->torch[i].txr_height);
		data->torch[i].addr = mlx_get_data_addr(data->torch[i].img, \
		&data->torch[i].bits_per_pixel, &data->torch[i].line_length, \
		&data->torch[i].endian);
		free(tmp2);
	}
}
