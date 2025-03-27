/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:53:24 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/27 22:03:16 by ecymer           ###   ########.fr       */
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
		data->player.orientation = degree_to_radian(90);
	else if (c == 'S')
		data->player.orientation = degree_to_radian(270);
	dir_x = cos(data->player.orientation);
	dir_y = sin(data->player.orientation);
	data->player.plane_x = 0.66 * dir_y;
	data->player.plane_y = -0.66 * dir_x;
}

void	find_players_pos(t_data *data, char **split_lines)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (split_lines[i])
	{
		j = 0;
		while (split_lines[i][j])
		{
			if (split_lines[i][j] == 'N' || split_lines[i][j] == 'S' \
			|| split_lines[i][j] == 'W' || split_lines[i][j] == 'E')
			{
				data->player.pos_y = i + 0.5;
				data->player.pos_x = j + 0.5;
				check_dir(data, split_lines[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	flood_fill(t_data *data, int *len, t_vector2 point)
{
	if (point.x == 0 || point.y == 0)
		return (clean_up(data, -1), free(len), error("Map is not closed1", 0));
	if (data->map[point.y][point.x] == '0')
		data->map[point.y][point.x] = 'F';
	if (data->map[point.y][point.x + 1] == '0' && ++point.x)
		flood_fill(data, len, point);
	else if (!ft_strchr("NSEW12DF", data->map[point.y][point.x + 1]))
		return (clean_up(data, -1), free(len), error("Map is not closed2", 0));
	if (data->map[point.y][point.x - 1] == '0' && point.x--)
		flood_fill(data, len, point);
	else if (!ft_strchr("NSEW12DF", data->map[point.y][point.x - 1]))
		return (clean_up(data, -1), free(len), error("Map is not closed3", 0));
	if (data->map[point.y + 1] && len[point.y + 1] >= point.x && \
		data->map[point.y + 1][point.x] == '0' && ++point.y)
		flood_fill(data, len, point);
	else if (!data->map[point.y + 1] || len[point.y + 1] < point.x || \
			!ft_strchr("NSEW12DF", data->map[point.y + 1][point.x]))
		return (clean_up(data, -1), free(len), error("Map is not closed4", 0));
	if (len[point.y - 1] >= point.x && \
		data->map[point.y - 1][point.x] == '0' && point.y--)
		flood_fill(data, len, point);
	else if (len[point.y - 1] < point.x || \
			!ft_strchr("NSEW12DF", data->map[point.y - 1][point.x]))
		return (clean_up(data, -1), free(len), error("Map is not closed5", 0));
}

void	validate_map(t_data *data)
{
	int			*len;
	t_vector2	point;

	len = map_line_len(data->map);
	find_players_pos(data, data->map);
	point.x = (int)data->player.pos_x;
	point.y = (int)data->player.pos_y;
	flood_fill(data, len, point);
	free(len);
}



//111111111
//10N000000001
//100000000001
//100000000001
//100000000001
//100000001111
//111111111

