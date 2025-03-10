/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:27:50 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/10 19:36:07 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_data(t_data *data, char *line, int fd)
{
	int	i;

	i = -1;
	while (++i <= 5)
	{
		if (i <= 3 && !data->txr[i].path)
			return (clean_up(data, fd), free(line), error("Missing texture", 0));
		else if (i <= 3 && validate_map_format(data->txr[i].path, ".xpm"))
			return (clean_up(data,fd), free(line), \
			error("Wrong texture format", 0));	
		else if (i >= 4 && data->txr[i].rgb_letter[0] == -1)
			return (clean_up(data,fd), free(line), error("No color!", 0));	
	}
}