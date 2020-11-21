/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 12:17:31 by iadrien           #+#    #+#             */
/*   Updated: 2020/11/21 12:18:41 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			save_write_in_file(char *s, t_args *arg)
{
	int		fd;

	if (!s || !arg)
		exit_error("bad string",1);
	if (!(fd = open(arg->arg, O_CREAT | O_APPEND | O_RDWR, 0644)))
		exit_error("\"echo f\" hello", 1);
	if (arg->next && arg->next->state == 5)
		close(fd);
	else
	{
		ft_putstr_fd(s, fd);
		close(fd);
	}
}

void			write_in_file(char *s, t_args *arg)
{
	int		fd;

	if (!s || !arg)
		exit_error("bad string",1);
	if (!(fd = open(arg->arg, O_CREAT | O_TRUNC | O_RDWR, 0644)))
		exit_error("open problem", 1);
	if (arg->next && arg->next->state == 3)
		close(fd);
	else
	{
		ft_putstr_fd(s, fd);
		close(fd);
	}
}

