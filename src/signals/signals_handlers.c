/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 21:59:03 by amayor            #+#    #+#             */
/*   Updated: 2021/03/10 12:34:13 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handler_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		ft_putstr_fd(g_username, 1);
		write(1, "$ ", 3);
		g_signal_flag = 2;
		g_r_code = 130;
	}
}

// TODO: возможно не нужна, тогда убрать
void	handler_sigquit(int sig)
{
	if(sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
}