/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_writer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 00:23:22 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/30 16:38:56 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_len(uintptr_t nbr, int nbr2, int div)
{
	int	i;

	i = 0;
	if (nbr2 < 0)
		i++;
	if (nbr2 != 0)
		while (nbr2 && i++ >= 0)
			nbr2 /= div;
	else if (nbr != 0)
		while (nbr && i++ >= 0)
			nbr /= div;
	else
		i++;
	return (i);
}

int	print_width(ssize_t width, int type)
{
	char	c;
	int		i;

	i = 0;
	if (type == 0)
		c = ' ';
	else
		c = '0';
	while (i++ < width)
		write(1, &c, 1);
	return (i - 1);
}

ssize_t	print_precision(ssize_t prec, ssize_t len)
{
	ssize_t		i;

	i = len - 1;
	if (prec == -1 || prec <= len)
		return (0);
	while (++i < prec)
		write(1, "0", 1);
	return (i - len);
}

size_t	get_precision(char *flag, size_t len, int nbr)
{
	size_t	precision;
	int		end;

	end = get_modi(flag, -1);
	precision = 0;
	while (ft_isdigit(flag[end]))
		end++;
	if (flag[end] == '.')
		while (ft_isdigit(flag[++end]))
			precision = (precision * 10) + flag[end] - 48;
	else
		return (-1);
	if (precision == 0)
		return (0);
	if (nbr < 0)
		precision++;
	if (len > precision)
		return (len);
	return (precision);
}

size_t	get_width(char *flag)
{
	size_t	width;
	int		end;

	end = get_modi(flag, -1);
	width = 0;
	if (flag[end] != '.')
		while (ft_isdigit(flag[end++]))
			width = (width * 10) + flag[end - 1] - 48;
	else
		width = -1;
	return (width);
}
