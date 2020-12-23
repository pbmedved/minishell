/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 21:59:03 by amayor            #+#    #+#             */
/*   Updated: 2020/12/22 23:03:37 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handler_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		ft_putstr_fd(USERNAME, 1);
		write(1, "$ ", 3);
		SIGNAL_FLAG = 2;
		GLOBAL_R_CODE = 130;
	}
}

// TODO: возможно не нужна, тогда убрать
void	handler_sigquit(int sig)
{
	if(sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
}