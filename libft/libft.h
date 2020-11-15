/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 23:21:31 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/28 13:11:30 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# define HT				9
# define CR				13
# define NUL			0
# define DEL			127

typedef struct			s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;
int						ft_atoi(const char *str);
void					ft_bzero(void *s, size_t n);
void					*ft_calloc(size_t num, size_t size);
void					*ft_memcpy(void *dst, const void *src, size_t n);
int						ft_isalnum(int ch);
int						ft_isalpha(int ch);
int						ft_isascii(int ch);
int						ft_isdigit(int ch);
int						ft_isprint(int ch);
void					*ft_memccpy(void *dst, const void *src,\
						int c, size_t n);
void					*ft_memchr (const void *arr, int c, size_t n);
int						ft_memcmp(const void *memptr1,\
						const void *memptr2, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memmove(void *dst,\
						const void *src, size_t n);
void					*ft_memset(void *memptr, int val, size_t num);
char					*ft_strchr(const char *str, int ch);
char					*ft_strdup(const char *str);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
size_t					ft_strlcpy (char *dst, const char *src, size_t size);
size_t					ft_strlen(const char *str);
int						ft_strncmp(const char *str1,\
						const char *str2, size_t n);
char					*ft_strnstr (const char *big,\
						const char *little, size_t len);
char					*ft_strrchr (const char *str, int ch);
int						ft_tolower(int ch);
int						ft_toupper(int ch);
void					ft_putchar(char c);
void					ft_putstr(char const *s);
void					ft_putendl_fd(char *s, int fd);
void					ft_memdel(void **ap);
char					*ft_substr(char const *s,\
						unsigned int start, size_t len);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);
char					**ft_split(char const *s, char c);
char					*ft_itoa(int n);
char					*ft_strjoin(char const *s1,\
						char const *s2);
char					*ft_strmapi(char const *s,\
						char (*f)(unsigned int, char));
char					*ft_strtrim(char const *s1, char const *set);
t_list					*ft_lstnew(void *content);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstclear(t_list **lst, void (*del)(void*));
int						ft_lstsize(t_list *lst);
void					ft_lstadd_back(t_list **lst, t_list *new);
void					ft_lstadd_front(t_list **lst, t_list *new);
void					ft_lstdelone(t_list *lst, void (*del)(void*));
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),\
						void (*del)(void *));
void					ft_lstiter(t_list *lst, void (*f)(void *));
#endif
