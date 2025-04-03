/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:43:16 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/02 22:48:10 by ecymer           ###   ########.fr       */
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

void	init_torch(t_data *data)
{
	int		i;
	char	*path;
	char	*tmp;
	char	*tmp2;

	i = -1;
	while (++i < 6)
	{
		tmp = ft_itoa(i);
		path = ft_strjoin("./torch/frame", tmp);
		free(tmp);
		tmp2 = ft_strjoin(path, ".xpm");
		free(path);
		data->torch[i].txr_height = 64;
		data->torch[i].txr_width = 64;
		data->torch[i].img = mlx_xpm_file_to_image(data->mlx, \
		tmp2, &data->torch[i].txr_width, &data->torch[i].txr_height);
		data->torch[i].addr = mlx_get_data_addr(data->torch[i].img, \
		&data->torch[i].bits_per_pixel, &data->torch[i].line_length, \
		&data->torch[i].endian);
		free(tmp2);
	}
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

	data->current_anim = 0;
	init_textures(data);
	init_keys(data);
	init_torch(data);
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
	calc_proportions(data);
}
