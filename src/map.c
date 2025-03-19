/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:25:30 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/19 20:38:05 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_chars(t_data *data, int fd, char *map_lines)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map_lines[i])
	{
		if (map_lines[i] == '0' || map_lines[i] == '1' || map_lines[i] == ' ' \
		|| map_lines[i] == '2' || map_lines[i] == '\n')
			i++;
		else if (map_lines[i] == 'N' || map_lines[i] == 'S' \
		|| map_lines[i] == 'W' || map_lines[i] == 'E')
		{
			i++;
			j++;
		}
		else
			return (clean_up(data, fd), free(map_lines), \
			error("Wrong char in map", 0));
		if (j == 2)
			return (clean_up(data, fd), free(map_lines), \
			error("Too many players", 0));
	}
	if (j == 0)
		return (clean_up(data, fd), free(map_lines), error("No players", 0));
}

void	create_map(t_data *data, char *line, int fd)
{
	char	*map_lines;
	char	*tmp_map_line;
	char	**split_map_lines;

	map_lines = ft_strdup("");
	while (line)
	{
		tmp_map_line = map_lines;
		map_lines = ft_strjoin(tmp_map_line, line);
		free(tmp_map_line);
		free(line);
		line = get_next_line(fd);
	}
	validate_chars(data, fd, map_lines);
	close(fd);
	split_map_lines = ft_split(map_lines, "\n");
	data->map = split_map_lines;
	validate_map(data, split_map_lines);
}
