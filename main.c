/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 09:24:37 by iadrien           #+#    #+#             */
/*   Updated: 2020/11/16 21:46:17 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"



void 		preallocated(t_vars *vars)
{
	if (!(vars->buff = ft_calloc(BUFF_SIZE, sizeof(char))))
		exit_error("Malloc error\n", errno);
	vars->state = 1;
	vars->comm = NULL;
	vars->env = NULL;
}

char			*str_parser(char *buff, int *n)
{
	int			i;
	int			brack;
	int			brack_2;
	char		*new_s;

	new_s = ft_calloc(1,1);
	i = 0;
	brack = 0;
	brack_2 = 0;
	while (buff[i] && (!ft_strchr(" |;", buff[i]) || brack || brack_2))
	{
		if (buff[i] == '\'')
		{
			brack ? brack-- : brack++;
			i++;
		}
		else if (buff[i] == '"' && !brack)
		{
			brack_2 ? brack_2-- : brack_2++;
			i++;
		}
		else if (buff[i] == 92 && !brack)
		{
			i++;
			new_s = str_reallocpy(new_s, buff[i++]);
		}
		else
			new_s = str_reallocpy(new_s, buff[i++]);
	}
	*n = i;
	return (new_s);
}

void		buff_parser(t_vars *vars, char *buff)
{
	int n;
	t_command 	*new_comm;
	t_args		*new_arg;
	while (*buff)
	{
		new_comm = command_new();
		new_comm->command = str_parser(buff, &n);
		buff += n;
		while (*buff == ' ')
			buff++;
		while (*buff && !ft_strchr("|;", *buff))
		{
			new_arg = arg_new();
			new_arg->arg = str_parser(buff, &n);
			arg_add(&new_comm->args,new_arg);
			buff += n;
			while (*buff == ' ')
				buff++;
		}
		command_add(&vars->comm, new_comm);
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
//		if (0 > read(1,vars->buff, BUFF_SIZE))
//			exit_error("Read error\n", errno);
		ft_strlcpy(vars->buff, "echo '\"lol\"'", 200);
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
		preallocated(&vars);
		env_save(&vars, envp);
		command_getter(&vars);
	}
	free(vars.buff);
	dell_all_env(&vars.env);
	return (0);
}
