/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 21:37:33 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/12 19:19:37 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd, int print_min)
{
	char	c;
	int		i;

	i = 1;
	if (n < 0 && print_min && i++)
		write(fd, "-", 1);
	if (n / 10 != 0)
		i += ft_putnbr_fd((n / 10) * ((n > 0) - (n < 0)), fd, print_min);
	c = '0' + (n % 10) * ((n > 0) - (n < 0));
	write(fd, &c, 1);
	return (i);
}
