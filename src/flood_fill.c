/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:53:24 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/12 18:19:20 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	is_map_playable(t_data *data, char **split_lines)
{
	int	i;

	i = -1;
	while (split_lines[++i])
		if (ft_strchr(split_lines[i], '0'))
			return (clean_up(data, -1), error("Map is not playable", 0));
}

void	change_tile(t_data *data, t_vector2 point)
{
	if (data->map[point.y][point.x] == '0')
		data->map[point.y][point.x] = 'F';
	else if (data->map[point.y][point.x] == '2')
		data->map[point.y][point.x] = 'D';
}

void	flood_fill(t_data *data, int *len, t_vector2 point)
{
	if (point.x == 0 || point.y == 0 || point.x + 1 == len[point.y])
		return (clean_up(data, -1), free(len), error("Map is not closed", 0));
	change_tile(data, point);
	if (ft_strchr("02", data->map[point.y][point.x + 1]))
		flood_fill(data, len, (t_vector2){point.x + 1, point.y});
	else if (!ft_strchr("NSEW1DF", data->map[point.y][point.x + 1]))
		return (clean_up(data, -1), free(len), error("Map is not closed", 0));
	if (ft_strchr("02", data->map[point.y][point.x - 1]))
		flood_fill(data, len, (t_vector2){point.x - 1, point.y});
	else if (!ft_strchr("NSEW1DF", data->map[point.y][point.x - 1]))
		return (clean_up(data, -1), free(len), error("Map is not closed", 0));
	if (data->map[point.y + 1] && len[point.y + 1] >= point.x && \
		ft_strchr("02", data->map[point.y + 1][point.x]))
		flood_fill(data, len, (t_vector2){point.x, point.y + 1});
	else if (!data->map[point.y + 1] || len[point.y + 1] < point.x || \
			!ft_strchr("NSEW1DF", data->map[point.y + 1][point.x]))
		return (clean_up(data, -1), free(len), error("Map is not closed", 0));
	if (len[point.y - 1] >= point.x && \
		ft_strchr("02", data->map[point.y - 1][point.x]))
		flood_fill(data, len, (t_vector2){point.x, point.y - 1});
	else if (len[point.y - 1] < point.x || \
			!ft_strchr("NSEW1DF", data->map[point.y - 1][point.x]))
		return (clean_up(data, -1), free(len), error("Map is not closed", 0));
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
	is_map_playable(data, data->map);
	free(len);
}
