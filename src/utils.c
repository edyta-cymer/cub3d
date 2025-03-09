/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:47:03 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/09 20:19:18 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
}
