/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 10:48:50 by iadrien           #+#    #+#             */
/*   Updated: 2020/07/22 15:35:59 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			find_end(const char *arg)
{
	int			i;

	i = 0;
	while (!ft_strchr("cspdiuoxXfn%", *arg))
	{
		arg++;
		i++;
	}
	return (i);
}

static int			by_param(va_list param, t_plist *mods)
{
	if (mods->type == '\0')
		return (0);
	if (ft_strchr("cC", mods->type))
		return (print_c(va_arg(param, int), mods));
	if (mods->type == '%')
		return (print_c('%', mods));
	if (mods->type == 's')
		return (print_s(va_arg(param, char*), mods));
	if (mods->type == 'p')
		return (convert_num(va_arg(param, unsigned long), mods, 16));
	if (ft_strchr("di", mods->type))
		return (prefix_d(param, mods));
	if (ft_tolower(mods->type) == 'x')
		return (prefix_x(param, mods));
	if (mods->type == 'u')
		return (prefix_u(param, mods));
	if (mods->type == 'n')
		return (to_n(va_arg(param, int*), mods));
	if (mods->type == 'o')
		return (convert_num(va_arg(param, long), mods, 8));
	return (0);
}

int					ft_printf(const char *arg, ...)
{
	t_plist			mods;
	va_list			ap;
	int				d;

	mods.curent_len = 0;
	va_start(ap, arg);
	while (*arg != '\0')
	{
		if (*arg == '%' && arg++)
		{
			get_specs(&mods, arg, ap);
			if ((d = by_param(ap, &mods)) < 0)
				return (d);
			mods.curent_len += d;
			arg += find_end(arg);
		}
		else
			mods.curent_len += write(1, arg, 1);
		*arg ? arg++ : 0;
	}
	va_end(ap);
	return (mods.curent_len);
}
