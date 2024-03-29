/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:39:08 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/20 23:23:09 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>

int		ft_atoi(const char *str, int *result);
int		ft_atoi_mod(const char *str, int *result);
int		ft_atod(const char *str, double *res);
int		ft_atod_mod(const char *str, double *res);
int		ft_atoll(const char *str, long long *result);
char	*ft_itoa(int n);
char	*ft_xitoa(int n);

void	*ft_calloc(size_t count, size_t size);
void	*ft_xcalloc(size_t count, size_t size);

int		ft_isalpha(int x);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);

int		ft_toupper(int c);
int		ft_tolower(int c);

// writing to an fd

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// memory functions

void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *str, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

// string functions

size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

// string allocating functions

char	*ft_strdup(const char *s1);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_xstrdup(const char *s1);
char	*ft_xstrjoin(const char *s1, const char *s2);
char	*ft_xstrmapi(const char *s, char (*f)(unsigned int, char));
char	*ft_xstrtrim(const char *s1, const char *set);
char	*ft_xsubstr(const char *s, unsigned int start, size_t len);

char	**ft_split(const char *s, char c);
char	**free_splits(char **splits);
size_t	split_count(char **splits);

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
