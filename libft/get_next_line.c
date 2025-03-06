/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:37:13 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/30 17:02:40 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	append_buffor(int fd, t_linelst *lst)
{
	char	*new_buffor;
	char	*tmp;
	int		count;

	new_buffor = (char *)malloc(BUFFER_SIZE + 1);
	if (!new_buffor)
		return (-1);
	count = read(fd, new_buffor, BUFFER_SIZE);
	if (count <= 0)
	{
		free(new_buffor);
		return (count);
	}
	new_buffor[count] = '\0';
	if (!lst->buffor)
		lst->buffor = ft_strdup("");
	tmp = lst->buffor;
	lst->buffor = ft_strjoin(tmp, new_buffor);
	free(tmp);
	free(new_buffor);
	if (!lst->buffor)
		return (-1);
	return (count);
}

static char	*extract_line(t_linelst *lst)
{
	int		i;
	char	*line;
	char	*new_buff;

	i = 0;
	while (lst->buffor[i] && lst->buffor[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	ft_strlcpy(line, lst->buffor, i + 2);
	new_buff = ft_strdup(lst->buffor + i + (lst->buffor[i] == '\n'));
	free(lst->buffor);
	lst->buffor = new_buff;
	return (line);
}

static t_linelst	*find_or_create_lst(t_linelst **head, int fd)
{
	t_linelst	*lst;

	lst = *head;
	while (lst)
	{
		if (lst->fd == fd)
			return (lst);
		lst = lst->next;
	}
	lst = malloc(sizeof(t_linelst));
	if (!lst)
		return (NULL);
	lst->fd = fd;
	lst->buffor = NULL;
	lst->next = *head;
	*head = lst;
	return (lst);
}

static void	free_lst(t_linelst **head, int fd)
{
	t_linelst	*tmp;
	t_linelst	*prev;

	tmp = *head;
	prev = NULL;
	while (tmp)
	{
		if (tmp->fd == fd)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*head = tmp->next;
			free(tmp->buffor);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

char	*get_next_line(int fd)
{
	static t_linelst	*head;
	t_linelst			*lst;
	char				*line;
	int					count;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	lst = find_or_create_lst(&head, fd);
	if (!lst)
		return (NULL);
	count = 1;
	while (!ft_strchr(lst->buffor, '\n') && count > 0)
		count = append_buffor(fd, lst);
	if (count == -1 || (count == 0 && (!lst->buffor || !*lst->buffor)))
	{
		free_lst(&head, fd);
		return (NULL);
	}
	line = extract_line(lst);
	return (line);
}
