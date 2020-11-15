/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_specs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 17:08:01 by iadrien           #+#    #+#             */
/*   Updated: 2020/07/20 18:05:20 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					zero_with_minus_plus(const char *arg, t_plist *mods)
{
	size_t			index;

	index = 0;
	mods->zero = 0;
	mods->minus = 0;
	mods->acc_bool = 0;
	mods->plus = 0;
	mods->plus_bool = 0;
	mods->hash = *arg == '#' && !index++ ? 1 : 0;
	while (arg[index] == '0' && (mods->zero = 1))
		index++;
	while (arg[index] == '-' && (mods->minus = 1) && (index++))
		mods->zero = 0;
	while (arg[index] == '+' && (mods->plus = 1))
	{
		mods->plus_bool = 1;
		index++;
	}
	while (arg[index] == '-' && (mods->minus = 1) && (index++))
		mods->zero = 0;
	while (arg[index] == '0' && (index++))
		mods->zero = mods->minus ? 0 : 1;
	return (index);
}

int					mods_wight(t_plist *mods, const char *arg, va_list param)
{
	int				i;

	mods->width = 0;
	i = 0;
	if (*arg != '.')
	{
		mods->width = *arg == '*' ? va_arg(param, int) : ft_atoi(arg);
		if (mods->width < 0)
			mods->minus = 1;
		mods->width *= mods->width < 0 ? -1 : 1;
		while (ft_isdigit(arg[i]) || arg[i] == '*')
			i++;
	}
	return (i);
}

int					mods_acc(t_plist *mods, const char *arg, va_list param)
{
	int				i;

	i = 0;
	mods->acc = 0;
	mods->acc_bool = 0;
	if (*arg == '.')
	{
		mods->acc_bool = 1;
		arg++;
		mods->acc = *arg == '*' ? va_arg(param, int) : ft_atoi(arg);
		mods->acc_bool = mods->acc < 0 ? 0 : 1;
		mods->acc = mods->acc < 0 ? 0 : mods->acc;
		while (ft_isdigit(arg[i]) || arg[i] == '*')
			i++;
		i++;
	}
	return (i);
}

void				get_specs(t_plist *mods, const char *arg, va_list param)
{
	mods->space = 0;
	mods->prefix = 0;
	while (*arg == ' ' && (mods->space = 1))
		arg++;
	arg += zero_with_minus_plus(arg, mods);
	arg += mods_wight(mods, arg, param);
	arg += mods_acc(mods, arg, param);
	mods->prefix = ft_strchr("lh", *arg) && *arg ? *arg++ : 0;
	mods->prefix += ft_strchr("lh", *arg) && *arg ? *arg++ : 0;
	mods->type = ft_strchr("cspdiuoxXfn%", *arg) && *arg ? *arg : 0;
}
