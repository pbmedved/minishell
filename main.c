/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 09:24:37 by iadrien           #+#    #+#             */
/*   Updated: 2020/11/16 16:45:03 by iadrien          ###   ########.fr       */
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

int			arg_parser(char *buff, t_args **arg)
{
	t_args		*new_arg;
	int			i;

	i = 0;
	while (*buff && !ft_strchr("|;", *buff))
	{
		new_arg = arg_new();
		while (*buff && !ft_strchr(" |;", *buff))
		{
			new_arg->arg = str_reallocpy(new_arg->arg, *buff);
			buff++;
			i++;
			if (*buff == 92)
			{
				new_arg->arg = str_reallocpy(new_arg->arg, *buff);
				buff++;
				i++;
			}
		}
		arg_add(arg, new_arg);
		while (*buff == ' ')
		{
			buff++;
			i++;
		}
	}
	return (i);
}

int			command_parser(char *buff, t_vars *vars)
{
	int i;
	t_command *new_comm;

	i = 0;
	new_comm = command_new();
	while (*buff && !ft_strchr(" |;", *buff))
	{
		new_comm->command = str_reallocpy(new_comm->command, *buff);
		buff++;
		i++;
	}
	while (*buff == ' ')
	{
		buff++;
		i++;
	}
	i += arg_parser(buff, &new_comm->args);
	command_add(&vars->comm, new_comm);
	return (i);
}

void		buff_parser(t_vars *vars, char *buff)
{
	while (*buff)
	{
		buff += command_parser(buff, vars);
	}
}

void 		call_echo(t_args *args)
{
	t_args *res;
	int n;

	n = 1;
	res = args;
	if (!ft_strncmp(args->arg,"-n",2))
	{
		n = 0;
		res = res->next;
	}
	while (res)
	{
		ft_printf("%s",res->arg);
		if (res->next)
			ft_printf(" ");
		res = res->next;
	}
	n ? ft_printf("\n") : ft_printf("");
}

void 		command_handler(t_command *comm)
{
	if (comm && !ft_strncmp(comm->command, "echo", 10))
	{
		call_echo(comm->args);
	}

}

void 		command_getter(t_vars *vars, t_env *env)
{
	for (int i = 0; i < 5; ++i)
	{
		ft_printf("%s$ ", env->promt);
//		if ((read(1, vars->buff, BUFF_SIZE)) < 0)
//			exit_error("Read error\n", errno);
		ft_strlcpy(vars->buff, "echo lol", 100);
		buff_parser(vars, vars->buff);
		command_handler(vars->comm);
		dell_all_command(&vars->comm);
		ft_bzero(vars->buff, BUFF_SIZE);
//		free(vars->buff);
//		free(vars->env.promt);
	}
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
	free(vars.buff);
	free(vars.env.promt);
	return d;
}
