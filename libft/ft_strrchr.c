/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:54:33 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/30 17:06:44 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	last_index;

	i = -1;
	last_index = -1;
	while (s[++i])
		if (s[i] == (char)c)
			last_index = i;
	if (s[i] == (char)c)
		last_index = i;
	if (last_index != -1)
		return ((char *)&(s[last_index]));
	return (0);
}
