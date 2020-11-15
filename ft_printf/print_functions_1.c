/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 17:04:28 by iadrien           #+#    #+#             */
/*   Updated: 2020/07/22 16:33:06 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					print_c(int c, t_plist *mods)
{
	size_t			width;
	int				d;

	d = 0;
	width = mods->width;
	while (width && width-- > 1 && !mods->minus)
		d += write(1, mods->zero ? "0" : " ", 1);
	d += write(1, &c, 1);
	while (width && width--)
		d += write(1, " ", 1);
	return (d);
}

int					print_s(char *s, t_plist *mods)
{
	int				width;
	int				acc;
	int				d;

	if (!s)
		s = "(null)";
	acc = mods->acc_bool ? mods->acc : (int)ft_strlen(s);
	acc = acc > (int)ft_strlen(s) ? (int)ft_strlen(s) : acc;
	width = mods->width < acc ? 0 : mods->width;
	d = 0;
	while (!mods->minus && width > 0 && width-- > acc)
		d += write(1, mods->zero ? "0" : " ", 1);
	d += write(1, s, acc);
	width -= d;
	while (width && width-- > 0)
		d += write(1, " ", 1);
	return (d);
}

int					print_p(char *s, t_plist *mods)
{
	int				width;
	int				d;
	int				acc;

	acc = mods->acc - (int)ft_strlen(s);
	if (!s)
		s = "(null)";
	d = 0;
	width = mods->width - 2;
	width -= *s == '0' && mods->acc_bool ? 0 : (int)ft_strlen(s);
	while (!mods->minus && width > 0 && width--)
		d += write(1, mods->zero ? "0" : " ", 1);
	d += write(1, "0x", 2);
	while (acc-- > 0)
		d += write(1, "0", 1);
	d += *s == '0' && mods->acc_bool && mods->acc == 0 ? \
	0 : (int)write(1, s, ft_strlen(s));
	while (width && width-- > 0)
		d += write(1, " ", 1);
	return (d);
}

int					print_d_x(char *s, t_plist *mods, t_final *final)
{
	int				d;

	d = 0;
	if (*s == '-')
		s++;
	d += write(1, " ", mods->space ? 1 : 0);
	d += write(1, final->plus ? "+" : "-", final->w_zero &&\
	!mods->acc_bool && final->sign-- ? 1 : 0);
	while (final->l_w-- > 0)
		d += write(1, final->w_zero && !mods->acc_bool ? "0" : " ", 1);
	d += write(1, final->plus ? "+" : "-", final->sign-- > 0 ? 1 : 0);
	while (final->acc-- > 0)
		d += write(1, "0", 1);
	if (*s == '0' && mods->acc_bool)
		d += write(1, "0", mods->acc ? 1 : 0);
	else
		d += write(1, s, ft_strlen(s));
	while (final->r_w-- > 0)
		d += write(1, " ", 1);
	return (d);
}

int					to_n(int *n, t_plist *mods)
{
	*n = mods->curent_len;
	return (0);
}
