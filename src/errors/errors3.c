/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 23:23:17 by iadrien           #+#    #+#             */
/*   Updated: 2021/03/29 09:26:31 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			end_of_file_error(void)
{
	ft_putstr_fd("-bash: syntax error: unexpected end of file\n", 2);
}

void			to_many_args_error(void)
{
	ft_putstr_fd("-bash: exit: too many arguments\n", 2);
}
