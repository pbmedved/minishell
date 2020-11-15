/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:47:15 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/04 22:22:39 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_fd(int n, int fd)
{
	int		i;

	if (n < 0)
	{
		if (n == -2147483648)
		{
			ft_putstr_fd("-2", fd);
			n = 147483648;
		}
		else
		{
			ft_putchar_fd('-', fd);
			n *= -1;
		}
	}
	i = 1;
	while (n / i > 9)
		i *= 10;
	while (i /= 10 != 1)
	{
		ft_putchar_fd(n / i + 0x30, fd);
		n %= i;
		i /= 10;
	}
}
