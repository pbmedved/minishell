/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 10:41:58 by iadrien           #+#    #+#             */
/*   Updated: 2020/07/22 15:35:47 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# define PREF_L 108
# define PREF_LL 216
# define PREF_H 104
# define PREF_HH 208

typedef struct		s_plist
{
	int				minus;
	int				print_minus;
	int				plus;
	int				plus_bool;
	int				space;
	int				width;
	int				zero;
	int				acc_bool;
	int				acc;
	int				hash;
	int				prefix;
	char			type;
	int				curent_len;
}					t_plist;
typedef struct		s_final_list
{
	int				w_zero;
	int				l_w;
	int				r_w;
	int				acc;
	int				minus;
	int				space;
	int				sign;
	int				plus;
}					t_final;
int					ft_printf(const char *c, ...);
size_t				ft_numlen(long long n, int base);
void				ft_prf_itoa_base(long long n, int base, char *buff);
void				ft_lowcase(char *s);
void				ft_uppercase(char *s);
void				parse_mods_num(t_plist *mods, t_final *final, char *s);
int					convert_num(long long d, t_plist *mods, int base);
int					print_c(int c, t_plist *mods);
int					print_s(char *s, t_plist *modsr);
int					print_d_x(char *s, t_plist *mods, t_final *final);
int					print_p(char *s, t_plist *mods);
int					zero_with_minus_plus(const char *arg, t_plist *mods);
void				get_specs(t_plist *mods, const char *arg, va_list param);
int					prefix_d(va_list param, t_plist *mods);
int					prefix_u(va_list param, t_plist *mods);
int					prefix_x(va_list param, t_plist *mods);
size_t				ft_numlen_uns(unsigned long n, int base);
void				ft_prf_itoa_hex_p(unsigned long n, int base, char *buf);
int					ft_isdigit(int ch);
int					ft_atoi(const char *str);
int					ft_tolower(int ch);
int					ft_toupper(int ch);
size_t				ft_strlen(const char *str);
char				*ft_strchr(const char *str, int ch);
int					to_n(int *n, t_plist *mods);
#endif
