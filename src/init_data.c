/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:43:16 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/09 19:38:01 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_map_format(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len >= 4)
		return (ft_strcmp(&str[len - 4], ".cub"));
	return (-1);
}
int	file_opener(char *filepath)
{
	int fd;
	
	if (validate_map_format(filepath) != 0)
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
	data->textures[0].id_texture = NO;
	data->textures[1].id_texture = SO;
	data->textures[2].id_texture = WE;
	data->textures[3].id_texture = EA;
	data->textures[4].id_texture = F;
	data->textures[5].id_texture = C;
	while (++i <= 5)
	{
		data->textures[i].path = NULL;
		data->textures[i].colors_letter[0] = -1;
		data->textures[i].colors_letter[1] = -1;
		data->textures[i].colors_letter[2] = -1;
	}
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
	if (ft_strcmp(split_line[0], "NO") == 0 && !data->textures[0].path)
		data->textures[0].path = ft_strdup(split_line[1]);
	else if (ft_strcmp(split_line[0], "SO") == 0 && !data->textures[1].path)
		data->textures[1].path = ft_strdup(split_line[1]);
	else if (ft_strcmp(split_line[0], "WE") == 0 && !data->textures[2].path)
		data->textures[2].path = ft_strdup(split_line[1]);
	else if (ft_strcmp(split_line[0], "EA") == 0 && !data->textures[3].path)
		data->textures[3].path = ft_strdup(split_line[1]);
	else if ((ft_strcmp(split_line[0], "F") == 0 && !data->textures[4].path) \
	|| data->textures[4].colors_letter[0] != -1)
		ft_handle_colors(data, split_line, fd, line);
	else if ((ft_strcmp(split_line[0], "C") == 0 && !data->textures[5].path) \
	|| data->textures[5].colors_letter[0] != -1)
		ft_handle_colors(data, split_line, fd, line);
	else 
		return (ft_free_split(split_line), clean_up(data, fd), \
		free(line), error("Wrong id or a duplicate", 0), -1);
	ft_free_split(split_line);
	return (0);
}

void	ft_handle_colors(t_data *data, char **split_line, int fd, char *line)
{
	char	**split_colors;
	int	i;
	
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
	data->textures[i].colors_letter[0] = ft_color_atoi(split_colors[0]);
	data->textures[i].colors_letter[1] = ft_color_atoi(split_colors[1]);
	data->textures[i].colors_letter[2] = ft_color_atoi(split_colors[2]);
	if (data->textures[i].colors_letter[0] > 255 \
	|| data->textures[i].colors_letter[1] > 255 \
	|| data->textures[i].colors_letter[2] > 255 \
	|| data->textures[i].colors_letter[0] < 0 \
	|| data->textures[i].colors_letter[1] < 0 \
	|| data->textures[i].colors_letter[2] < 0) 
		return (ft_free_split(split_colors), ft_free_split(split_line), \
			clean_up(data, fd), free(line), error("Wrong color number", 0));
	ft_free_split(split_colors);
}

void	init_data(char *filepath, t_data *data)
{
	int	fd;
	char	*line;
	char	**split_line;
	
	init_textures(data);
	fd = file_opener(filepath);
	line = get_next_line(fd);
	while (line)
	{
		split_line = ft_split(line, " \n");
		if (add_path(data, split_line, fd, line) == -1)
			break;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	clean_up(data, fd);
}

