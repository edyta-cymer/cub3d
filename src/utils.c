/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:47:03 by ecymer            #+#    #+#             */
/*   Updated: 2025/03/06 19:01:18 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_handling(char *message, int type)
{
	if(type == 0)
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