/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:25:30 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/13 21:54:13 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate_chars(char *map_lines)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (map_lines[i])
	{
		if (map_lines[i] == '0' || map_lines[i] == '1' \
		 || map_lines[i] == ' ' || map_lines[i] == '2' \
		 || map_lines[i] == '\n')
			i++;
		else if (map_lines[i] == 'N' || map_lines[i] == 'S' \
		|| map_lines[i] == 'W' || map_lines[i] == 'E')
		{
			i++;	
			j++;
			
		}
		else
			return (-1);
		if (j == 2)
			return (-1);
	}
	return (1);
}



static int	validate_walls(char **split_map_lines)
{
	// 
}

 int	validate_map(char *map_lines)
 {
	char **split_map_lines;

	split_map_lines = ft_split(map_lines, "\n");
	if (validate_first_last_line(split_map_lines) != 0)
		return (-1);
	validate_walls(split_map_lines);
 }

void	create_map(t_data *data, char *line, int fd)
{
	char *map_lines;
	char *tmp_map_line;
	
	map_lines = ft_strdup("");
	while (line)
	{
		tmp_map_line = map_lines;
		map_lines = ft_strjoin(tmp_map_line, line);
		free(tmp_map_line);
		free(line);
		line = get_next_line(fd);
	}
	if (validate_chars(map_lines) != 1)
	{
		clean_up(map_lines, fd);
		error("Wrong chars in the map", 0);
	}
	validate_map(map_lines);	
}



/*
// sprawdzić czy mapa się składa z 1, 0, N, S , W, E, 2
// mapa musi być zamknięta 1-
// NIE można przechodzic przez ściany, ale można przez drzwi 


*/

////   111
//    111000111
//	110000001
//	111111111

// char **str    [indeks 0 - musi mieć same 1]
// [indeks ostatni musi miec same 1 ]
// w każdej linijce pierwsze element musi byc 1
// ostatnia liczba w linijce musi byc 1



// DOPISAĆ error handling w validate_chars!!!
