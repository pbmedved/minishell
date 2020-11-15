/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:50:42 by iadrien           #+#    #+#             */
/*   Updated: 2020/07/06 14:50:42 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					prefix_d(va_list param, t_plist *mods)
{
	if (mods->prefix == PREF_L)
		return (convert_num(va_arg(param, long), mods, 10));
	if (mods->prefix == PREF_LL)
		return (convert_num(va_arg(param, long long), mods, 10));
	return (convert_num(va_arg(param, int), mods, 10));
}

int					prefix_u(va_list param, t_plist *mods)
{
	if (mods->prefix == PREF_L)
		return (convert_num(va_arg(param, unsigned long), mods, 10));
	if (mods->prefix == PREF_LL)
		return (convert_num(va_arg(param, unsigned long long), mods, 10));
	if (mods->prefix == PREF_H || mods->prefix == PREF_HH)
		return (convert_num(va_arg(param, unsigned int), mods, 10));
	return (convert_num(va_arg(param, unsigned int), mods, 10));
}

int					prefix_x(va_list param, t_plist *mods)
{
	if (mods->prefix == PREF_L)
		return (convert_num(va_arg(param, unsigned long), mods, 16));
	if (mods->prefix == PREF_LL)
		return (convert_num(va_arg(param, unsigned long long), mods, 16));
	if (mods->prefix == PREF_H || mods->prefix == PREF_HH)
		return (convert_num(va_arg(param, unsigned int), mods, 16));
	return (convert_num(va_arg(param, unsigned int), mods, 16));
}
