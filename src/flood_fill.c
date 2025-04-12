/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:53:24 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/12 17:21:17 by ecymer           ###   ########.fr       */
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
	int	j;

	(void)data;
	i = 0;
	j = 0;
	while (split_lines[i])
	{
		j = 0;
		while (split_lines[i][j])
		{
			if (split_lines[i][j] == '0')
				return (clean_up(data, -1), error("Map is not playable", 0));
			j++;
		}
		i++;
	}
}

void	flood_fill(t_data *data, int *len, t_vector2 point)
{
	if (point.x == 0 || point.y == 0 || point.x + 1 == len[point.y])
		return (clean_up(data, -1), free(len), error("Map is not closed1", 0));
	if (data->map[point.y][point.x] == '0')
		data->map[point.y][point.x] = 'F';
	else if (data->map[point.y][point.x] == '2')
		data->map[point.y][point.x] = 'D';
	if (ft_strchr("02", data->map[point.y][point.x + 1]))
	{
		++point.x;
		flood_fill(data, len, point);
		--point.x;
	}
	else if (!ft_strchr("NSEW1DF", data->map[point.y][point.x + 1]))
		return (clean_up(data, -1), free(len), error("Map is not closed2", 0));
	if (ft_strchr("02", data->map[point.y][point.x - 1]))
	{
		point.x--;
		flood_fill(data, len, point);
		point.x++;
	}
	else if (!ft_strchr("NSEW1DF", data->map[point.y][point.x - 1]))
		return (clean_up(data, -1), free(len), error("Map is not closed3", 0));
	if (data->map[point.y + 1] && len[point.y + 1] >= point.x && \
		ft_strchr("02", data->map[point.y + 1][point.x]))
	{
		++point.y;
		flood_fill(data, len, point);
		--point.y;
	}
	else if (!data->map[point.y + 1] || len[point.y + 1] < point.x || \
			!ft_strchr("NSEW1DF", data->map[point.y + 1][point.x]))
		return (clean_up(data, -1), free(len), error("Map is not closed4", 0));
	if (len[point.y - 1] >= point.x && \
		ft_strchr("02", data->map[point.y - 1][point.x]))
	{
		point.y--;
		flood_fill(data, len, point);
		point.y++;
	}
	else if (len[point.y - 1] < point.x || \
			!ft_strchr("NSEW1DF", data->map[point.y - 1][point.x]))
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
	is_map_playable(data, data->map);
	free(len);
}
