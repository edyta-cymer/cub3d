/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:47:03 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/09 18:04:43 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_decimal(t_data *data, t_texture id_txr)
{
	int	result;

	if (id_txr == F)
	{
		result = (data->txr[4].rgb_letter[0] << 16) + \
		(data->txr[4].rgb_letter[1] << 8) + data->txr[4].rgb_letter[2];
	}
	else
	{
		result = (data->txr[5].rgb_letter[0] << 16) + \
		(data->txr[5].rgb_letter[1] << 8) + data->txr[5].rgb_letter[2];
	}
	return (result);
}

void	clear_images(t_data *data)
{
	int	i;

	i = -1;
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	while (++i <= 3)
		if (data->txr[i].image.img != NULL)
			mlx_destroy_image(data->mlx, data->txr[i].image.img);
	i = -1;
	while (++i < 6)
		if (data->torch[i].img != NULL)
			mlx_destroy_image(data->mlx, data->torch[i].img);
	if (data->door.img)
		mlx_destroy_image(data->mlx, data->door.img);
}

void	clean_up(t_data *data, int fd)
{
	int		i;
	char	*line;

	i = -1;
	while (++i <= 5)
		if (data->txr[i].path)
			free(data->txr[i].path);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	if (fd != -1)
		close(fd);
	if (data->map)
		ft_free_split(data->map);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	clear_images(data);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

int	ft_color_atoi(const char *nptr)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (nptr[i] >= 9 && nptr[i] <= 13)
		i++;
	while (nptr[i] && ft_isdigit(nptr[i]))
		count = (count * 10) + ((nptr[i++] - 48));
	if (nptr[i])
		return (-1);
	return (count);
}

void	error(char *message, int type)
{
	if (type == 0)
	{
		printf("Error\n%s\n", message);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Error\n%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}
