/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:36:10 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/13 11:57:12 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 10

# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h> 
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

typedef struct s_linelst
{
	int					fd;
	int					current_line;
	char				*buffor;
	struct s_linelst	*next;
}			t_linelst;

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_bzero(void *s, size_t m);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd, ssize_t ammount);
void	ft_putendl_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int fd, int print_min);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strcat(char *dest, char *src);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_strrchr(const char *s, int c);
char	*ft_itoa(int n);
char	*ft_strcpy(char *dest, char *src);
char	**ft_split(char *str, char *charset);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
int		ft_abs(int n);
int		ft_lstsize(t_list *lst);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_atoi(const char *nptr);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);
ssize_t	print_precision(ssize_t prec, ssize_t len);
size_t	get_precision(char *flag, size_t len, int nbr);
size_t	get_width(char *flag);
ssize_t	calculate_width(ssize_t width, ssize_t precision, ssize_t len,
			ssize_t d);
char	*validate_flag(char *str, size_t length);
int		handle_str(char *s, char *flag, int chrs);
int		handle_unsigned(unsigned int d, char *flag, int chrs);
int		handle_ptr(uintptr_t d, char *flag, int chrs);
int		handle_hex(unsigned int d, char *flag, int chrs, int capital);
int		handle_decimal(int d, char *flag, int chrs);
int		find_zero(const char *str, int con);
int		ft_printf(const char *str, ...);
int		find_in_set(char c, const char *charset);
int		get_flag_length(const char *str, int per_index);
int		get_modi(const char *str, int per_i);
int		ft_putunbr_fd(unsigned int n, int fd);
int		ft_putnbr_base(unsigned int nbr, char *base);
int		ft_putptr(uintptr_t nbr);
int		get_len(uintptr_t nbr, int nbr2, int div);
int		print_width(ssize_t width, int type);

#endif
