/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 07:18:15 by iadrien           #+#    #+#             */
/*   Updated: 2020/12/26 20:58:19 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		print_prompt(t_vars *vars)
{

	ft_putstr_fd(vars->prompt, 1);
	write(1, "$ ", 2);
}

void 			command_set_state(t_command *comm)
{
	t_command	*res;
	t_args		*args;

	res = comm;
	while (res)
	{
		args = res->args;
		while (args)
		{
			if (args->state == 8)
			{
				res->state = 3;
				break;
			}
			args = args->next;
		}
		res = res->next;
	}
}
void 			permission_error(char *prog, char *file)
{
	write(2, prog, ft_strlen(prog));
	write(2, ":", 1);
	write(2, file, ft_strlen(file));
	write(2, ": Permission denied\n", 21);
}

void 			command_set_fd_out(t_command *comm, char redir, char *file)
{
	int fd;

	if ((fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644)) < 0)
	{
		permission_error(comm->command, file);
		return ;
	}
	comm->fd_out = fd;
}

void 			command_set_fd_in(t_command *comm, char redir, char *file)
{
	int fd;

	if ((fd = open(file, O_RDWR, 0644)) < 0)
	{
		permission_error(comm->command, file);
		return ;
	}
	comm->fd_in = fd;
}

void 			command_set_fd_out_end(t_command *comm, char *file)
{
	int fd;

	if ((fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644)) < 0)
	{
		permission_error(comm->command, file);
		return ;
	}
	comm->fd_out = fd;
}

void 			newline_error()
{
	write(2,"-bash: syntax error near unexpected token `newline'\n", 53);
}

/*
** Определяет тип редиректа и вызывает соотвествующую функцию.
**
*/
int			redirect_fd_choose(t_command *comm, t_args *args)
{
	if (!args->next)
	{
		newline_error();
		return (0);
	}
	args->next->state = 2;
	if(!ft_strncmp(args->arg, ">", ft_strlen(args->arg)))
		command_set_fd_out(comm, '>', args->next->arg);
	else if(!ft_strncmp(args->arg, "<", ft_strlen(args->arg)))
		command_set_fd_in(comm, '<', args->next->arg);
	else if(!ft_strncmp(args->arg, ">>", ft_strlen(args->arg)))
		command_set_fd_out_end(comm, args->next->arg);
	return (1);
}

void	 		redirect_fd_set(t_command *command)
{
	t_args		*args;
	t_command   *comm;

	comm = command;
	while (comm)
	{
		args = comm -> args;
		while (args) {
			if (args->state == 2)
			{
				if (redirect_fd_choose(comm,args))
					args = args -> next;
			}
			args = args -> next;
		}
		comm = comm -> next;
	}
}

void		command_fix(t_command **comm)
{
	int i;
	t_command *res;

	res = *comm;
	command_set_state(res);
	while (res)
	{
		redirect_fd_set(res);
		i = -1;
		while (res->command[++i])
			res->command[i] = (char)ft_tolower(res->command[i]);
		res = res->next;
	}
}
// static int check_sigquit(char *b)
// {
// 	if (*b == '^')
// 	{
// 		*b = ' ';
// 		return (0);
// 	}
// 	return (1);
// }
/*
** Основной цикл шелла.
** Читает и выполняет команды.
** Читает посимвольно и пересоздает буфер, куда записывает комаду.
**
** Обнуление флага сигнала SIGNAL_FLAG = 0 здесь нужно для того,
** чтобы не печатать два раза приглашение командной строки.
** Дело в том что если перехватывается SIGINT, то внутри обработчика так же
** печатается приглашение, для обработки SIGINT аналогично башу, когда просто
** пустая строка.
** Если не делать флаг, то приглашение командной строки может печататься
** два раза в случае перехвата его в дочернем процессе,
** например cat
*/
void 		command_getter(t_vars *vars, char **envp)
{
	char 	b;

	while(vars->state)
	{
		// signal(SIGQUIT, SIG_IGN);
		signal(SIGQUIT, handler_sigquit);
		signal(SIGINT, handler_sigint);
		if (SIGNAL_FLAG == 0)
			print_prompt(vars);
		SIGNAL_FLAG = 0; // нужно в случае когда сигнал перехватывается в потомке, см. в описании функции
		if (!vars->buff)
		{
			if (!(vars->buff = ft_calloc(1,1)))
				exit_error("Malloc error", errno);
			while((read(vars->fd[0], &b, 1)) && b != '\n')
				vars->buff = str_reallocpy(vars->buff, b);
		}
		buff_parser(vars, vars->buff, envp);
//		command_fix(&vars->comm);
//		command_handler(vars->comm, vars, envp);
//		dell_all_command(&vars->comm);
		free(vars->buff);
		vars->buff = NULL;
	}
}