/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:53:24 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/20 00:14:21 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	*map_line_len(char **split_lines, int *i)
{
	int	j;
	int	*len;

	j = 0;
	while (split_lines[*i])
		(*i)++;
	len = malloc(*i * sizeof(int));
	while (j < i)
	{
		len[j] = ft_strlen(split_lines[j]);
		i++;
		j++;
	}
	return (len);
}

void	check_dir(t_data *data, char c)
{
	if (c == "N")
		data->t_player.orientation = degree_to_radian(0);
	else if (c == "S")
		data->t_player.orientation = degree_to_radian(180);
	else if (c == "E")
		data->t_player.orientation = degree_to_radian(90);
	else if (c == "W")
		data->t_player.orientation = degree_to_radian(270);
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
			if (split_lines[i][j] == "N" || split_lines[i][j] == "S" \
			|| split_lines[i][j] == "W" || split_lines[i][j] == "E")
			{
				data->t_player.pos_y = i;
				data->t_player.pos_x = j;
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
		return (clean_up(data, -1), free(len), error("Map is not closed", 0));
	if (data->map[point.y][point.x] == '0')
		data->map[point.y][point.x] = 'F';
	if (data->map[point.y][point.x + 1] == '0' && ++point.x)
		flood_fill(data, len, point);
	else if (!ft_strchr("NSEW12DF", data->map[point.y][point.x + 1]))
		return (clean_up(data, -1), free(len), error("Map is not closed", 0));
	if (data->map[point.y][point.x - 1] == '0' && point.x--)
		flood_fill(data, len, point);
	else if (!ft_strchr("NSEW12DF", data->map[point.y][point.x - 1]))
		return (clean_up(data, -1), free(len), error("Map is not closed", 0));
	if (len[point.y + 1] >= point.x && data->map[point.y + 1][point.x] == \
		'0' && ++point.y)
		flood_fill(data, len, point);
	else if (len[point.y + 1] < point.x || !ft_strchr("NSEW12DF", \
			data->map[point.y + 1][point.x]))
		return (clean_up(data, -1), free(len), error("Map is not closed", 0));
	if (data->map[point.y - 1][point.x] == '0' && point.y--)
		flood_fill(data, len, point);
	else if (len[point.y - 1] < point.x || !ft_strchr("NSEW12DF", \
			data->map[point.y + 1][point.x]))
		return (clean_up(data, -1), free(len), error("Map is not closed", 0));
}

void	validate_map(t_data *data)
{
	int	i;
	int	*len;
	t_vector2 point;

	i = 0;
	len = map_line_len(data->map, &i);
	find_players_pos(data, data->map);
	point.x = (int)data->t_player.pos_x;
	point.y = (int)data->t_player.pos_y;
	flood_fill(data, len, point);
}



//111111111
//10N000000001
//100000000001
//100000000001
//100000000001
//100000001111
//111111111

