/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flag_length.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:10 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/30 16:39:05 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_in_set(char c, const char *charset)
{
	int	i;

	i = -1;
	while (charset[++i])
		if (c == charset[i])
			return (c);
	return (0);
}

static int	get_rest(const char *str, int i)
{
	int	total;

	total = 0;
	while (ft_isdigit(str[i]))
	{
		i++;
		total++;
	}
	if (str[i] == '.')
	{
		i++;
		total++;
	}
	while (ft_isdigit(str[i]))
	{
		i++;
		total++;
	}
	if (!find_in_set(str[i], "cspdiuxX"))
		return (-1);
	total++;
	return (total);
}

int	get_modi(const char *str, int per_index)
{
	char	*currently_found;
	int		total;
	int		i;

	i = per_index;
	total = 0;
	currently_found = (char *)malloc(6 * sizeof(char));
	if (!currently_found)
		return (-1);
	ft_bzero((void *)currently_found, 6 * sizeof(char));
	while (str[++i] && find_in_set(str[i], "# -+0"))
	{
		if (str[i] == '0' && find_in_set('0', currently_found))
			break ;
		else if (!find_in_set(str[i], currently_found))
			currently_found[i - 1 - per_index] = find_in_set(str[i], "# -+0");
		total++;
	}
	free(currently_found);
	return (total);
}

int	get_flag_length(const char *str, int per_index)
{
	int	total;
	int	tmp;

	total = get_modi(str, per_index);
	if (total == -1)
		return (total);
	tmp = total;
	total += get_rest(str, per_index + 1 + total);
	if (tmp > total)
		return (-1);
	return (total);
}
