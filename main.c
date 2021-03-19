/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 09:24:37 by iadrien           #+#    #+#             */
/*   Updated: 2021/03/19 22:56:54 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void		preallocated(t_vars *vars)
{
	vars->buff = NULL;
	vars->state = 1;
	vars->comm = NULL;
	vars->env = NULL;
	vars->fd[0] = dup(0);
	vars->fd[1] = dup(1);
	vars->prompt = NULL;
	vars->global_r_code = 0;
}

int				g_signal_flag;
char			*g_username;
int				g_r_code;

/*
** TODO: убирать выводимый "^D" в заполненной строке при нажатии Ctrl-D
** Основной цикл шелла.
** Читает и выполняет команды.
** Читает посимвольно и пересоздает буфер, куда записывает комаду.
**
** Обнуление флага сигнала g_signal_flag = 0 здесь нужно для того,
** чтобы не печатать два раза приглашение командной строки.
** Дело в том что если перехватывается SIGINT, то внутри обработчика так же
** печатается приглашение, для обработки SIGINT аналогично башу, когда просто
** пустая строка.
** Если не делать флаг, то приглашение командной строки может печататься
** два раза в случае перехвата его в дочернем процессе,
** например cat
*/
static void			prompt_print(t_vars *vars)
{
	if (g_signal_flag == 0)
	{
		ft_putstr_fd(vars->prompt, 1);
		write(1, "$ ", 2);
	}
}

void			command_getter(t_vars *vars, char **envp)
{
	char		b;
	ssize_t		res;

	prompt_print(vars);
	while (vars->state)
	{
		signal(SIGQUIT, handler_sigquit);
		signal(SIGINT, handler_sigint);
		g_signal_flag = 0;
		if (!vars->buff)
		{
			if (!(vars->buff = ft_calloc(1, 1)))
				exit_error("Malloc error", errno);
			while (((res = read(vars->fd[0], &b, 1)) && b != '\n') || res == 0)
				input_handler(res, b, vars);
		}
		buff_parser(vars, vars->buff, envp);
		free(vars->buff);
		vars->buff = NULL;
		prompt_print(vars);
	}
}

int				main(int argc, char **argv, char **envp)
{
	t_vars		vars;

	preallocated(&vars);
	g_signal_flag = 0;
	g_r_code = 0;
	if (argc != 1 && argc != 3)
		exit_error("bad param", -1);
	if (argc == 3 && argv[1][0] == '-' && argv[1][1] == 'c' && !argv[1][2])
		vars.buff = str_reallocpy_str(vars.buff, argv[2]);
	env_save(&vars, envp);
	vars.prompt = ft_strdup(env_take(&vars, "USER"));
	g_username = vars.prompt;
	command_getter(&vars, envp);
	free(vars.prompt);
	free(vars.buff);
	vars.buff = 0;
	dell_all_env(&vars.env);
	return (0);
}
