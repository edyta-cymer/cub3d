/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:43:16 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/06 20:23:46 by ecymer           ###   ########.fr       */
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
		error_handling("Wrong file format", 0);
	fd = open(filepath, O_WRONLY);
	if (fd == -1)
		error_handling(NULL, 1);
	return (fd);
}

void	init_data(char *filepath, t_data *data)
{
	int	fd;
	char	*line;
	
	fd = file_opener(filepath);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}