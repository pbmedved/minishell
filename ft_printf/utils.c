/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:36:39 by iadrien           #+#    #+#             */
/*   Updated: 2020/07/15 15:24:39 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_lowcase(char *s)
{
	while (*s != '\0')
	{
		*s = (char)ft_tolower(*s);
		s++;
	}
}

void		ft_uppercase(char *s)
{
	while (*s != '\0')
	{
		*s = (char)ft_toupper(*s);
		s++;
	}
}

size_t		ft_numlen(long long n, int base)
{
	size_t	len;

	len = 1;
	if (n < 0 && (n *= -1))
		base == 10 ? len++ : 0;
	while ((n /= base))
		len++;
	return (len);
}

size_t		ft_numlen_uns(unsigned long n, int base)
{
	size_t	len;

	len = 1;
	if (n < 0 && (n *= -1))
		base == 10 ? len++ : 0;
	while ((n /= base))
		len++;
	return (len);
}
