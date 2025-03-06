/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:14:44 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/30 16:39:13 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_zero(const char *str, int con)
{
	int	i;
	int	found;

	found = 0;
	i = -1;
	while (str[++i])
	{
		if (ft_isdigit(str[i]) && found)
			return (1);
		else if (ft_isdigit(str[i]) > '0')
			return (0);
		else if (str[i] == '0')
		{
			if (con)
				return (1);
			found = 1;
		}
	}
	return (found);
}

static void	find_modi(const char *str, size_t len, char *cur)
{
	int	i;

	i = 0;
	if ((str[len - 1] == 'x' || str[len - 1] == 'X')
		&& find_in_set('#', str) != 0)
		cur[i++] = '#';
	if (find_in_set(' ', str) != 0 && find_in_set('+', str) == 0
		&& (str[len - 1] == 'i' || str[len - 1] == 'd' || str[len - 1] == 'u'))
		cur[i++] = ' ';
	if (find_in_set('+', str) != 0 && (str[len - 1] == 'i'
			|| str[len - 1] == 'd' || str[len - 1] == 'u'))
		cur[i++] = '+';
	if (find_in_set('-', str) != 0)
		cur[i++] = '-';
	if (find_zero(str, 0) && find_in_set('-', str) == 0
		&& find_in_set('.', str) == 0 && (str[len - 1] == 'i'
			|| str[len - 1] == 'd' || str[len - 1] == 'u'
			|| str[len - 1] == 'x' || str[len - 1] == 'X'))
		cur[i++] = '0';
}

static void	validate_rest(const char *str, int *i, size_t len,
							int found)
{
	int	skip;

	skip = *i;
	while (str[skip] && (!ft_isdigit(str[skip]) || ft_isdigit(str[skip]) == 48)
		&& str[skip] != '.' && !find_in_set(str[skip], "cspdiuxX"))
		skip++;
	while (ft_isdigit(str[skip]))
	{
		skip++;
		(*i)++;
	}
	if (str[skip] == '.' && str[len - 1] != 'c' && str[len - 1] != 'p')
	{
		(*i)++;
		skip++;
		while (ft_isdigit(str[skip]))
		{
			skip++;
			(*i)++;
		}
	}
	(*i)++;
	while (found > 0 && --found)
		(*i)--;
}

char	*validate_flag(char *str, size_t length)
{
	int		i;
	int		j;
	char	currently_found[5];
	char	*new_flag;

	i = 0;
	ft_bzero(currently_found, 5);
	find_modi(str, length, currently_found);
	while (currently_found[i])
		i++;
	validate_rest(str, &i, length, ft_strlen(currently_found));
	new_flag = (char *)malloc((i + 2) * sizeof(char));
	if (!new_flag)
	{
		free(str);
		return (NULL);
	}
	j = -1;
	while (currently_found[++j])
		new_flag[j] = currently_found[j];
	while (str[length - i])
		new_flag[j++] = str[length - i--];
	new_flag[j] = 0;
	free(str);
	return (new_flag);
}
