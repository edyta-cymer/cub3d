/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:53:24 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/14 23:59:48 by ecymer           ###   ########.fr       */
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
	len = malloc(i);
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

void	flood_fill(t_data *data, char **split_lines)
{
	int	i;
	int	*len;

	i = 0;
	len = map_line_len(split_lines, &i);
	find_players_pos(data, split_lines);
}
