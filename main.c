/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 09:24:37 by iadrien           #+#    #+#             */
/*   Updated: 2020/11/15 23:41:19 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


void 		get_promt(t_env *env, char **envp)
{
	int i;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i],"USER=",5))
		i++;
	if (envp[i])
		env->promt = ft_strdup(envp[i]+5);
}

void 		preallocated(t_vars *vars)
{
	if (!(vars->buff = ft_calloc(BUFF_SIZE, sizeof(char))))
		exit_error("Malloc error\n", errno);
	vars->state = 1;
	vars->comm = NULL;
}

void		command_parser(t_vars *vars, char *buff)
{
	t_command 	*new_comm;
	t_args		*new_arg;
	new_comm = command_new();
	new_arg = arg_new();
	while (*buff && *buff != ' ')
	{
		new_comm->command = str_reallocpy(new_comm->command, *buff);
		buff++;
	}
	while (*buff)
	{
		while (*buff && *buff == ' ')
			buff++;
		while (*buff && *buff != ' ')
		{
			new_arg->arg = str_reallocpy(new_arg->arg, *buff);
			buff++;
		}
		arg_add(&new_comm->args, new_arg);
		command_add(&vars->comm, new_comm);
	}
}

void 		command_getter(t_vars *vars, t_env *env)
{
		ft_printf("%s$ ",env->promt);
		if ((read(1,vars->buff,BUFF_SIZE)) < 0)
			exit_error("Read error\n", errno);
//		ft_strlcpy(vars->buff, "echo lol", 100);
		command_parser(vars, vars->buff);
		ft_printf("%s\n", vars->comm->command);
		dell_all_command(&vars->comm);
//		ft_bzero(vars->buff, BUFF_SIZE);
		free(vars->buff);
		free(vars->env.promt);
}

int			main(int argc, char **argv, char **envp) {
	t_vars 	vars;
	char 	*s = argv[0];
	int d = argc;
	if (s) {
		get_promt(&vars.env, envp);
		preallocated(&vars);
		command_getter(&vars, &vars.env);
	}
	return d;
}
