/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:43:16 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/31 21:20:09 by ecymer           ###   ########.fr       */
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

void	init_textures(t_data *data)
{
	int	i;

	i = -1;
	data->txr[0].id_txr = NO;
	data->txr[1].id_txr = SO;
	data->txr[2].id_txr = WE;
	data->txr[3].id_txr = EA;
	data->txr[4].id_txr = F;
	data->txr[5].id_txr = C;
	data->map = NULL;
	data->window = NULL;
	data->img.img = NULL;
	while (++i <= 5)
	{
		data->txr[i].path = NULL;
		data->txr[i].rgb_letter[0] = -1;
		data->txr[i].rgb_letter[1] = -1;
		data->txr[i].rgb_letter[2] = -1;
	}
}

int	add_single_path(t_data *data, char **split_line, int fd, char *line)
{
	if (ft_strcmp(split_line[0], "NO") == 0 && !data->txr[0].path)
		return (data->txr[0].path = ft_strdup(split_line[1]), 0);
	else if (ft_strcmp(split_line[0], "SO") == 0 && !data->txr[1].path)
		return (data->txr[1].path = ft_strdup(split_line[1]), 0);
	else if (ft_strcmp(split_line[0], "WE") == 0 && !data->txr[2].path)
		return (data->txr[2].path = ft_strdup(split_line[1]), 0);
	else if (ft_strcmp(split_line[0], "EA") == 0 && !data->txr[3].path)
		return (data->txr[3].path = ft_strdup(split_line[1]), 0);
	else if ((ft_strcmp(split_line[0], "F") == 0 \
	&& data->txr[4].rgb_letter[0] == -1))
		ft_handle_colors(data, split_line, fd, line);
	else if (ft_strcmp(split_line[0], "C") == 0 \
	&& data->txr[5].rgb_letter[0] == -1)
		ft_handle_colors(data, split_line, fd, line);
	else
		return (ft_free_split(split_line), clean_up(data, fd), \
		free(line), error("Wrong id or a duplicate", 0), -1);
	
	return (0);
}

int	add_path(t_data *data, char **split_line, int fd, char *line)
{
	if (!split_line[0])
		return (ft_free_split(split_line), 0);
	if (ft_strchr(split_line[0], '1'))
		return (ft_free_split(split_line), -1);
	if (!split_line[1] || split_line[2])
		return (ft_free_split(split_line), clean_up(data, fd), \
	free(line), error("Wrong textures in file", 0), 0);
	add_single_path(data, split_line, fd, line);
	ft_free_split(split_line);
	return (0);
}

void	init_keys(t_data *data)
{
	data->keys.w = 0;
	data->keys.a = 0;
	data->keys.s = 0;
	data->keys.d = 0;
}

void	ft_handle_colors(t_data *data, char **split_line, int fd, char *line)
{
	char	**split_colors;
	int		i;

	if (ft_strcmp(split_line[0], "F") == 0)
		i = 4;
	else
		i = 5;
	split_colors = ft_split(split_line[1], ",");
	if (!split_colors[0] || !split_colors[1] || !split_colors[2] || \
		split_colors[3])
		return (ft_free_split(split_colors), ft_free_split(split_line), \
				clean_up(data, fd), free(line), \
				error("Wrong colors numbers in file", 0));
	data->txr[i].rgb_letter[0] = ft_color_atoi(split_colors[0]);
	data->txr[i].rgb_letter[1] = ft_color_atoi(split_colors[1]);
	data->txr[i].rgb_letter[2] = ft_color_atoi(split_colors[2]);
	if (data->txr[i].rgb_letter[0] > 255 \
	|| data->txr[i].rgb_letter[1] > 255 \
	|| data->txr[i].rgb_letter[2] > 255 \
	|| data->txr[i].rgb_letter[0] < 0 || data->txr[i].rgb_letter[1] < 0 \
	|| data->txr[i].rgb_letter[2] < 0)
		return (ft_free_split(split_colors), ft_free_split(split_line), \
			clean_up(data, fd), free(line), error("Wrong color number", 0));
	ft_free_split(split_colors);
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
