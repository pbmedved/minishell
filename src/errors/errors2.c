/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:05:14 by iadrien           #+#    #+#             */
/*   Updated: 2021/03/10 18:10:05 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				export_error(char *key, char *value)
{
	ft_printf("minishell: export: `%s=%s': not a valid identifier\n", \
	key, value);
	return (0);
}

void			permission_error(char *prog, char *file)
{
	write(2, prog, ft_strlen(prog));
	write(2, ":", 1);
	write(2, file, ft_strlen(file));
	write(2, ": Permission denied\n", 21);
}

void			newline_error(void)
{
	write(2, "-bash: syntax error near unexpected token `newline'\n", 53);
}
