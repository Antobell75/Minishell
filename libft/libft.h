/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:23:25 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/20 20:31:58 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;

}					t_list;

// PRINTF

typedef struct s_print
{
	va_list			args;
	const char		*format;
	int				di;
	unsigned int	lowerx;
	unsigned int	upperx;
	unsigned int	u;
	void			*ptr;
	int				count;
	int				check;
	int				i;
	int				fd;
}	t_print;

int					ft_pourcent(const char *str, va_list args, t_print *fptf);
int					ft_fprintf(int fd, const char *format, ...);
int					ft_putchar(char c, int fd);
int					ft_putstr(char *str, int count, int fd);
int					ft_printf_di(int n, int count, int fd);
int					ft_printf_lowerx(unsigned int n, int count, int fd);
int					ft_printf_upperx(unsigned int n, int count, int fd);
int					ft_printf_u(unsigned int n, int count, int fd);
int					ft_printf_p(void *ptr, int count, int check, int fd);

// LIBFT
int					ft_isalpha(int letter);
int					ft_isdigit(int nb);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
void				*ft_memset(void *s, int c, size_t n);
size_t				ft_strlen(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *string, int searchedChar);
char				*ft_strrchr(const char *string, int searchedChar);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *p1, const void *p2, size_t size);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
int					ft_atoi(const char *str);
char				*ft_strdup(const char *source);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
char				*ft_strndup(const char *src, int n);
int					ft_strcmp(const char *s1, const char *s2);

#endif
