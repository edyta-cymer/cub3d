/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:43:16 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/01 20:55:49 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_map_format(char *str, char *ext)
{
	size_t	len;

	len = ft_strlen(str);
	if (len >= 4)
		return (ft_strcmp(&str[len - 4], ext));
	return (-1);
}

int	file_opener(char *filepath)
{
	int	fd;

	if (validate_map_format(filepath, ".cub") != 0)
		error("Wrong file format", 0);
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		error(NULL, 1);
	return (fd);
}

void	init_keys(t_data *data)
{
	data->keys.w = 0;
	data->keys.a = 0;
	data->keys.s = 0;
	data->keys.d = 0;
}

void	init_data(char *filepath, t_data *data)
{
	int		fd;
	char	*line;
	char	**split_line;

	init_textures(data);
	init_keys(data);
	fd = file_opener(filepath);
	line = get_next_line(fd);
	while (line)
	{
		split_line = ft_split(line, " \n");
		if (add_path(data, split_line, fd, line) == -1)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	validate_data(data, line, fd);
	create_map(data, line, fd);
}
