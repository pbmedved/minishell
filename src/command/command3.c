/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 22:18:34 by amayor            #+#    #+#             */
/*   Updated: 2021/03/19 22:19:13 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void				dell_all_command(t_command **command)
{
	t_command		*main;
	t_command		*res;

	main = *command;
	while (main)
	{
		dell_all_args(&main->args);
		res = main->next;
		free(main->command);
		main->command = NULL;
		free(main);
		main = res;
	}
	*command = NULL;
}
