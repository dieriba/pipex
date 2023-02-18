/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:12:58 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/08 15:12:58 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define STRCMP_NULL_END -1000
# define SIZE_MAX 18446744073709551615UL
# include <unistd.h>
# include <stdlib.h>

char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2, char *s3, int pos_s3);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char *s, char c);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_itoa(long long n);

char		**ft_free_tab(char **tab);
char		**ft_dup_tab(char **to_copy, char *to_join);

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			find_end_word(char *s, char c, size_t k);
int			free_all_tab_split(char **tab, int len);
int			ft_char_index(char *line, char to_find);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_tab_len(char **tab);
int			ft_strcmp(char *s1, char *s2);
int			ft_putstr_fd(char *s, int fd);
int			ft_putendl_fd(char *s, int fd);
int			ft_putchar_fd(char c, int fd);
int			ft_numbered_str_only(char *line);
int			valid_double_split(char const *s, size_t i);
int			check_empty(int argc, char **argv);

size_t		ft_str_tab_len(char **tab);
size_t		ft_strlen(const char *s);
size_t		find_next_separator(char *to_parse, size_t i, char c);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);

void		ft_malloc_less_itoa(char **res, long long n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_free_elem(void **elem);
void		ft_putnbr_fd(int n, int fd);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		skip_split(char *to_parse, size_t *i, int quote);

long long	ft_atoi(const char *nptr);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int			ft_lstsize(t_list *lst);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
#endif
