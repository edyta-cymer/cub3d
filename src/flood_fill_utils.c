/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:20:49 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/12 17:21:09 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	*map_line_len(char **split_lines)
{
	int	j;
	int	*len;
	int	i;

	i = 0;
	j = 0;
	while (split_lines[i])
		i++;
	len = malloc(i * sizeof(int));
	while (j < i)
	{
		len[j] = ft_strlen(split_lines[j]);
		j++;
	}
	return (len);
}

void	check_dir(t_data *data, char c)
{
	float	dir_x;
	float	dir_y;

	if (c == 'E')
		data->player.orientation = degree_to_radian(0);
	else if (c == 'W')
		data->player.orientation = degree_to_radian(180);
	else if (c == 'N')
		data->player.orientation = degree_to_radian(270);
	else if (c == 'S')
		data->player.orientation = degree_to_radian(90);
	dir_x = cos(data->player.orientation);
	dir_y = sin(data->player.orientation);
	data->player.plane_x = -0.66 * dir_y;
	data->player.plane_y = 0.66 * dir_x;
}
