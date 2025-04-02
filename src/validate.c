/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:27:50 by ecymer            #+#    #+#             */
/*   Updated: 2025/04/02 18:29:52 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	xpm_to_image(t_data *data, int i)
{
	data->txr[i].txr_height = 64;
	data->txr[i].txr_width = 64;
	data->txr[i].image.img = mlx_xpm_file_to_image(data->mlx, \
	data->txr[i].path, &data->txr->txr_width, &data->txr->txr_height);
	data->txr[i].image.addr = mlx_get_data_addr(data->txr[i].image.img, \
	&data->txr[i].image.bits_per_pixel, &data->txr[i].image.line_length, \
	&data->txr[i].image.endian);
}

void	validate_data(t_data *data, char *line, int fd)
{
	int	i;
	int	check_file;

	i = -1;
	while (++i <= 5)
	{
		if (i <= 3 && !data->txr[i].path)
			return (clean_up(data, fd), free(line), \
				error("Missing texture", 0));
		else if (i <= 3 && validate_map_format(data->txr[i].path, ".xpm"))
			return (clean_up(data, fd), free(line), \
				error("Wrong texture format", 0));
		else if (i >= 4 && data->txr[i].rgb_letter[0] == -1)
			return (clean_up(data, fd), free(line), error("No color!", 0));
		else if (i <= 3)
		{
			check_file = open(data->txr[i].path, O_RDONLY);
			if (check_file == -1)
				return (clean_up(data, fd), free(line), error(NULL, 1));
			close(check_file);
			xpm_to_image(data, i);
		}
	}
}
