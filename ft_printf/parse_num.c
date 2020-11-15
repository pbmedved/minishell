/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:37:51 by iadrien           #+#    #+#             */
/*   Updated: 2020/07/22 15:37:14 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				parse_mods_num(t_plist *mods, t_final *final, char *s)
{
	final->minus = 0;
	final->plus = mods->plus;
	final->w_zero = mods->zero;
	if (*s == '-' && !(final->plus = 0))
		final->minus = 1;
	final->sign = final->plus || final->minus ? 1 : 0;
	final->acc = mods->acc - (int)ft_strlen(s);
	final->l_w = mods->width - (int)ft_strlen(s);
	final->l_w -= final->acc > 0 ? final->acc : 0;
	final->l_w += *s == '0' && mods->acc_bool &&\
	!mods->acc ? (int)ft_strlen(s) : 0;
	if (final->sign > 0 && mods->acc_bool && final->acc >= 0)
	{
		final->l_w--;
		final->acc++;
	}
	final->r_w = mods->minus ? final->l_w : 0;
	final->l_w = final->r_w ? 0 : final->l_w;
}

int					convert_num(long long num, t_plist *mods, int base)
{
	char			*d_p;
	size_t			len;
	t_final			final;
	int				d;

	if (mods->prefix == PREF_H)
		num = ft_strchr("uxX", mods->type) ? (unsigned short)num : (short)num;
	if (mods->prefix == PREF_HH)
		num = num < 0 ? (signed char)num : (unsigned char)num;
	len = ft_numlen(num, base);
	if (!(d_p = malloc(len + 1)))
		return (-1);
	if (mods->type == 'p')
		ft_prf_itoa_hex_p((unsigned long)num, 16, d_p);
	else
		ft_prf_itoa_base(num, base, d_p);
	mods->type == 'X' ? ft_uppercase(d_p) : ft_lowcase(d_p);
	parse_mods_num(mods, &final, d_p);
	d = mods->type == 'p' ? print_p(d_p, mods)\
	: print_d_x(d_p, mods, &final);
	free(d_p);
	return (d);
}

void				ft_prf_itoa_hex_p(unsigned long n, int base, char *buf)
{
	char			*dict;
	size_t			i;

	dict = "0123456789ABCDEFG";
	i = ft_numlen_uns(n, base);
	if (n < 0 && (n *= -1))
		base == 10 ? buf[0] = '-' : 0;
	buf[i--] = '\0';
	while ((n / base))
	{
		buf[i--] = dict[n % base];
		n = n / base;
	}
	buf[i] = dict[n];
}

void				ft_prf_itoa_base(long long n, int base, char *buf)
{
	char			*dict;
	size_t			i;

	dict = "0123456789ABCDEFG";
	i = ft_numlen(n, base);
	if (n < 0 && (n *= -1))
		base == 10 ? buf[0] = '-' : 0;
	buf[i--] = '\0';
	while ((n / base))
	{
		buf[i--] = dict[n % base];
		n = n / base;
	}
	buf[i] = dict[n];
}
