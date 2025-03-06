/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:54:01 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/02 23:04:35 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*find_lst;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	find_lst = *lst;
	while (find_lst->next != NULL)
		find_lst = find_lst->next;
	find_lst->next = new;
}
