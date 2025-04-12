/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:41:06 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/12 18:07:17 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	degree_to_radian(int degree)
{
	return ((double)degree * M_PI / 180.0);
}

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (size_t)1000) + (tv.tv_usec / 1000));
}

void	open_the_door(t_data *data, t_vector2 point1, int i)
{
	if (data->map[point1.y][point1.x] == 'D')
	{
		data->map[point1.y][point1.x] = 'O';
		data->opened_doors[i].coords.x = point1.x;
		data->opened_doors[i].coords.y = point1.y;
		data->opened_doors[i].opened = get_time();
	}
}

void	open_doors(t_data *data)
{
	t_vector2	point1;
	int			i;

	i = -1;
	while (++i < 64)
		if (data->opened_doors[i].coords.x == -1)
			break ;
	if (i == 64)
		return ;
	point1.x = (int)data->player.pos_x;
	point1.y = (int)data->player.pos_y;
	if (data->player.orientation > degree_to_radian(45) && \
		data->player.orientation < degree_to_radian(135))
		point1.y++;
	else if (data->player.orientation > degree_to_radian(135) && \
		data->player.orientation < degree_to_radian(225))
		point1.x--;
	else if (data->player.orientation > degree_to_radian(225) && \
		data->player.orientation < degree_to_radian(315))
		point1.y--;
	else
		point1.x++;
	open_the_door(data, point1, i);
}

void	close_doors(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 64)
	{
		if (data->opened_doors[i].coords.x == -1)
			continue ;
		if (get_time() - data->opened_doors[i].opened > 5000 && \
			((int)data->player.pos_x != data->opened_doors[i].coords.x || \
			(int)data->player.pos_y != data->opened_doors[i].coords.y))
		{
			data->map[data->opened_doors[i].coords.y]
			[data->opened_doors[i].coords.x] = 'D';
			data->opened_doors[i].coords.x = -1;
		}
	}
}
