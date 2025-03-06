/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 21:33:43 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/11 01:47:08 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd, ssize_t ammount)
{
	int	i;

	if (!s)
	{
		if (ammount >= 1 && ammount < 6)
			return (0);
		write(fd, "(null)", 6);
		return (6);
	}
	i = -1;
	if (ammount == -1)
		while (s[++i])
			write(fd, &s[i], 1);
	else
		while (s[++i] && i < ammount)
			write(fd, &s[i], 1);
	return (i);
}
