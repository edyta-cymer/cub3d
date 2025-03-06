/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 20:56:00 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/30 16:34:14 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	handle_flag(char *flag, va_list *arg_ls, int *c)
{
	size_t	len;

	len = ft_strlen(flag);
	if (flag[len - 1] == 'd' || flag[len - 1] == 'i')
		*c += handle_decimal(va_arg(*arg_ls, int), flag, 0);
	else if (flag[len - 1] == 'x')
		*c += handle_hex(va_arg(*arg_ls, unsigned int), flag, 0, 0);
	else if (flag[len - 1] == 'X')
		*c += handle_hex(va_arg(*arg_ls, unsigned int), flag, 0, 1);
	else if (flag[len - 1] == 'c')
	{
		if (!find_in_set('-', flag))
			*c += print_width(get_width(flag) - 1, 0);
		*c += ft_putchar_fd(va_arg(*arg_ls, int), 1);
		if (find_in_set('-', flag))
			*c += print_width(get_width(flag) - 1, 0);
	}
	else if (flag[len - 1] == 's')
		*c += handle_str(va_arg(*arg_ls, char *), flag, 0);
	else if (flag[len - 1] == 'p')
		*c += handle_ptr((uintptr_t)va_arg(*arg_ls, void *), flag, 0);
	else if (flag[len - 1] == 'u')
		*c += handle_unsigned(va_arg(*arg_ls, unsigned int), flag, 0);
}

static char	*get_flag(const char *str, int *i)
{
	char	*flag;
	size_t	len;
	int		total_length;

	total_length = get_flag_length(str, *i);
	if (total_length == -1)
		return (NULL);
	flag = ft_substr(str, (*i) + 1, total_length);
	if (flag == NULL)
		return (NULL);
	len = ft_strlen(flag);
	*i += len;
	flag = validate_flag(flag, len);
	if (flag == NULL)
		return (NULL);
	return (flag);
}

static int	write_flags(const char *str, va_list *arg_ls)
{
	int		i;
	int		chars;
	char	*flag;

	i = 0;
	chars = 0;
	while (str[i])
	{
		flag = NULL;
		if (str[i] == '%' && str[i + 1] != '%')
		{
			flag = get_flag(str, &i);
			if (flag == NULL)
				return (0);
			handle_flag(flag, arg_ls, &chars);
			free(flag);
		}
		else
		{
			write(1, &str[i], 1);
			chars++;
		}
		i = i + 1 + (str[i] == '%' && str[i + 1] == '%');
	}
	return (chars);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg_ls;
	int		chars;

	chars = 0;
	va_start(arg_ls, str);
	chars = write_flags(str, &arg_ls);
	va_end(arg_ls);
	return (chars);
}
