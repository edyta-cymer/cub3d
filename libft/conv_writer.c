/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_writer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:24:46 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/30 16:34:06 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(unsigned int nbr, char *base)
{
	int	baselength;
	int	i;

	i = 1;
	baselength = ft_strlen(base);
	if (baselength <= 1)
		return (0);
	if (nbr / baselength != 0)
		i += ft_putnbr_base(nbr / baselength, base);
	write(1, &base[nbr % baselength], 1);
	return (i);
}

int	ft_putptr(uintptr_t nbr)
{
	int		i;
	char	*hexes;

	i = 1;
	if (nbr == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	hexes = "0123456789abcdef";
	if (nbr / 16 != 0)
		i += ft_putptr(nbr / 16);
	write(1, &hexes[nbr % 16], 1);
	return (i);
}

int	ft_putunbr_fd(unsigned int n, int fd)
{
	char	c;
	int		i;

	i = 1;
	if (n / 10 != 0)
		i += ft_putunbr_fd(n / 10, fd);
	c = '0' + (n % 10);
	write(fd, &c, 1);
	return (i);
}

ssize_t	calculate_width(ssize_t width, ssize_t precision, ssize_t len,
			ssize_t d)
{
	if (precision == -1)
		return (width - len);
	if (precision == 0 && d == 0 && width == -1)
		return (0);
	else if (precision == 0 && d == 0)
		return (width);
	return (width - (precision >= len) * precision - (len > precision) * len);
}
