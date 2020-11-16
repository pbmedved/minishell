/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 09:24:37 by iadrien           #+#    #+#             */
/*   Updated: 2020/11/16 19:32:22 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"



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
	int			brack;
	int			brack_2;

	i = 0;
	brack = 0;
	brack_2 = 0;
	new_arg = arg_new();
	while (*buff && !ft_strchr("|;", *buff))
	{
		if (*buff == '\'')
		{
			brack ? brack-- : brack++;
			buff++;
			i++;
		}
		else if (*buff == 92)
		{
			if (brack)
			{
				new_arg->arg = str_reallocpy(new_arg->arg, *buff);
				buff++;
				i++;
			}
			else
			{
				buff++;
				new_arg->arg = str_reallocpy(new_arg->arg, *buff);
				buff++;
				i += 2;
			}
		}
		else if (*buff == '"')
		{
			if (brack)
			{
				new_arg->arg = str_reallocpy(new_arg->arg, *buff);
				buff++;
				i++;
			}
			else
			{
				brack_2 ? brack_2-- : brack_2++;
				buff++;
				i++;
			}

		}
		else if (*buff == ' ' && !brack_2)
		{
			arg_add(arg, new_arg);
			new_arg = arg_new();
			while (*buff && *buff == ' ')
			{
				buff++;
				i++;
			}
		}
		else
		{
			new_arg->arg = str_reallocpy(new_arg->arg, *buff);
			buff++;
			i++;
		}
	}
//	if (!*arg && !brack_2)
	arg_add(arg, new_arg);
//	else if (brack)
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

void			args_fix(t_args *args)
{
	if (args)
	{
		if (ft_strlen(args->arg) == 1 && args->arg[0] == 92)
			args->arg[0] = ' ';
	}
}
void			str_fix(t_command *comm)
{
	t_command	*comm_node;
	t_args		*args_node;

	comm_node = comm;
	while (comm_node)
	{
		args_node = comm_node->args;
		//comm fix
		while (args_node)
		{
			args_fix(args_node);
			args_node = args_node->next;
		}
		comm_node = comm_node->next;
	}
}

void		buff_parser(t_vars *vars, char *buff)
{
	while (*buff)
	{
		buff += command_parser(buff, vars);
	}
//	str_fix(vars->comm);
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
		call_echo(comm->args);
	else if (comm && !ft_strncmp(comm->command, "cd", 2))
		ft_printf("cd");
	else if (comm && !ft_strncmp(comm->command, "pwd", 3))
		ft_printf("pwd");
	else if (comm && !ft_strncmp(comm->command, "export", 6))
		ft_printf("export");
	else if (comm && !ft_strncmp(comm->command, "unset", 5))
		ft_printf("unset");
	else if (comm && !ft_strncmp(comm->command, "env", 3))
		ft_printf("env");
	else if (comm && !ft_strncmp(comm->command, "exit", 4))
		ft_printf("exit");
}

void 		command_getter(t_vars *vars)
{
	for (int i = 0; i < 100; ++i)
	{
		ft_printf("%s$ ", "USER:");
		if (0 > read(1,vars->buff, BUFF_SIZE))
			exit_error("Read error\n", errno);
//		ft_strlcpy(vars->buff, "echo '\\\\\\'", 200);
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
		env_save(&vars, envp);
		preallocated(&vars);
		command_getter(&vars);
	}
	free(vars.buff);
	return d;
}
