/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:25:30 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/01 21:34:28 by ecymer           ###   ########.fr       */
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
		if (map_lines[i] == '\n' && map_lines[i + 1] == '\n')
			return (clean_up(data, fd), free(map_lines), \
			error("Consecutive new lines.", 0));
		if (ft_strchr("01 2\n", map_lines[i]))
			i++;
		else if (ft_strchr("NSWE", map_lines[i]) && ++j)
			i++;
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
	free(map_lines);
	data->map = split_map_lines;
	validate_map(data);
}
