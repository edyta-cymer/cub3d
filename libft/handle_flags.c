/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 00:14:15 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/30 16:43:09 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handle_str(char *s, char *flag, int chrs)
{
	ssize_t	width;
	ssize_t	precision;
	ssize_t	len;

	if (!s)
		len = 6;
	else
		len = ft_strlen(s);
	width = get_width(flag);
	precision = get_precision(flag, 0, 0);
	if (precision >= 0 && precision < len)
		len = precision;
	width -= len;
	if (!find_in_set('-', flag) && width > 0)
		chrs += print_width(width, 0);
	chrs += ft_putstr_fd(s, 1, len);
	if (find_in_set('-', flag) && width > 0)
		chrs += print_width(width, 0);
	return (chrs);
}

int	handle_unsigned(unsigned int d, char *flag, int chrs)
{
	ssize_t	width;
	ssize_t	p;
	ssize_t	len;

	len = get_len(d, 0, 10);
	width = get_width(flag);
	p = get_precision(flag, len, 0);
	width = calculate_width(width, p, len, d);
	if (!find_in_set('-', flag) && width > 0)
		chrs += print_width(width, find_zero(flag, 1));
	chrs += print_precision(p, len);
	if (p != 0 || d != 0)
		chrs += ft_putunbr_fd(d, 1);
	if (find_in_set('-', flag) && width > 0)
		chrs += print_width(width, 0);
	return (chrs);
}

int	handle_ptr(uintptr_t d, char *flag, int chrs)
{
	ssize_t	width;
	ssize_t	precision;
	ssize_t	len;

	if (d == 0)
		len = 5;
	else
		len = get_len(d, 0, 16);
	width = get_width(flag);
	if (d > 0)
		precision = get_precision(flag, len, 0);
	else
		precision = 0;
	width = calculate_width(width, precision, len, 1);
	if (d > 0)
		width -= 2;
	if (!find_in_set('-', flag) && width > 0)
		chrs += print_width(width, 0);
	if (d > 0 && ++chrs && ++chrs)
		write(1, "0x", 2);
	chrs += print_precision(precision, len);
	chrs += ft_putptr(d);
	if (find_in_set('-', flag) && width > 0)
		chrs += print_width(width, 0);
	return (chrs);
}

int	handle_hex(unsigned int d, char *flag, int chrs, int capital)
{
	ssize_t	width;
	size_t	p;
	size_t	len;

	len = get_len(d, 0, 16);
	width = get_width(flag);
	p = get_precision(flag, len, 0);
	if (find_in_set('#', flag) && d > 0 && ++chrs && ++chrs)
		len += 2;
	width = calculate_width(width, p, len, d);
	if (!find_in_set('-', flag) && width > 0)
		chrs += print_width(width, find_zero(flag, 1));
	if (find_in_set('#', flag) && capital && d > 0)
		write(1, "0X", 2);
	else if (find_in_set('#', flag) && d > 0)
		write(1, "0x", 2);
	chrs += print_precision(p, len);
	if (capital && (p != 0 || d != 0))
		chrs += ft_putnbr_base(d, "0123456789ABCDEF");
	else if (p != 0 || d != 0)
		chrs += ft_putnbr_base(d, "0123456789abcdef");
	if (find_in_set('-', flag) && width > 0)
		chrs += print_width(width, 0);
	return (chrs);
}

int	handle_decimal(int d, char *flag, int chrs)
{
	ssize_t	width;
	ssize_t	precision;
	ssize_t	len;

	len = get_len(0, d, 10);
	if (d >= 0 && (find_in_set('+', flag) || find_in_set(' ', flag)) && ++chrs)
		len++;
	precision = get_precision(flag, len, d);
	width = calculate_width(get_width(flag), precision, len, d);
	if (!find_in_set('-', flag) && !find_zero(flag, 1) && width > 0)
		chrs += print_width(width, 0);
	if (d >= 0 && find_in_set('+', flag))
		write(1, "+", 1);
	else if (d >= 0 && find_in_set(' ', flag))
		write(1, " ", 1);
	else if (d < 0 && ++chrs)
		write(1, "-", 1);
	if (!find_in_set('-', flag) && find_zero(flag, 1) && width > 0)
		chrs += print_width(width, 1);
	chrs += print_precision(precision, len);
	if (precision != 0 || d != 0)
		chrs += ft_putnbr_fd(d, 1, 0);
	if (find_in_set('-', flag) && width > 0)
		chrs += print_width(width, 0);
	return (chrs);
}
