/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:42:30 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/19 12:44:15 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>
#include <fcntl.h>

static void		re_open_std(const uint8_t std, char *tty_name)
{
	int		fd;

	fd = open(tty_name, O_RDWR);
	if (std & CLOSED_STDIN)
		dup2(fd, STDIN_FILENO);
	if (std & CLOSED_STDOUT)
		dup2(fd, STDOUT_FILENO);
	if (std & CLOSED_STDERR)
		dup2(fd, STDERR_FILENO);
	if (fd >= 3)
		close(fd);
	return ;
}

void			do_nofork_redirect(void *context, void *data)
{
	uint8_t		*std;
	t_redirect	*redirect;

	redirect = data;
	std = context;
	if (redirect->from == STDIN_FILENO)
		*std |= CLOSED_STDIN;
	if (redirect->from == STDOUT_FILENO)
		*std |= CLOSED_STDOUT;
	if (redirect->from == STDERR_FILENO)
		*std |= CLOSED_STDERR;
	if (redirect->type & FD_DUP)
		dup2(redirect->to, redirect->from);
	else if (redirect->type & (FD_MOVE | FD_REDIRECT))
		dup2(redirect->to, redirect->from);
	else if (redirect->type & FD_CLOSE)
		close(redirect->from);
}

void			run_builtin(t_registry *shell, t_process *process)
{
	char			*tty_name;
	uint8_t			std;
	t_builtin		builtin;

	std = 0;
	tty_name = ttyname(STDIN_FILENO);
	if (process->process_type & IS_ALONE)
		ft_lstiter_ctx(process->redirects, &std, do_nofork_redirect);
	else
		ft_lstiter(process->redirects, do_redirect);
	builtin = ft_hmap_getdata(&shell->hash.blt, process->av[0]);
	process->status = builtin(shell, process->av);
	if (process->process_type & IS_ALONE)
		re_open_std(std, tty_name);
	ft_lstiter(process->redirects, close_redirect);
	process->completed = 1;
	return ;
}

int				get_failed_process(void *data, void *context)
{
	t_process	*current;

	(void)context;
	current = data;
	if (current->process_type & (IS_NOTFOUND | IS_OPEN_FAILED | IS_CRITICAL))
		return (TRUE);
	return (FALSE);
}

void			run_process(void *context, void *data)
{
	t_registry	*shell;
	t_process	*process;

	shell = context;
	process = data;
	if (get_process_type(shell, process) == FAILURE)
	{
		ft_dprintf(2, SH_GENERAL_ERROR SH_MALLOC_ERROR);
		return;
	}
	if (process->process_type & IS_NOTFOUND)
		ft_dprintf(2, SH_GENERAL_ERROR "%s" INTEPRETER_NOT_FOUND, process->av[0]);
	else if (process->process_type & IS_ASSIGN)
	{
		assign_intern(shell, process->env);
		process->env = NULL;
		process->completed = 1;
	}
	else if (process->process_type == (IS_ALONE | IS_BLT))
		run_builtin(shell, process);
	else
		fork_process(shell, process);
	return;
}

void	set_stopped(void *data)
{
	t_process	*process;

	process = data;
	process->stopped = TRUE;
	return ;
}

void			set_signaled(void *context, void *data)
{
	t_job		*job;
	uint32_t	*signo;

	job = data;
	signo = context;
	job->state |= KILLED;
	job->signo = *signo;
	ft_lstiter(job->processes, set_stopped);
	return ;
}

static uint8_t	do_i_run(t_registry *shell, t_job *job)
{
	if (job->state & KILLED)
		return (FALSE);
	else if (job->job_type & GROUP_AND)
	{
		if (!(shell->last_job_state & SUCCEDED))
			return (FALSE);
	}
	else if (job->job_type & GROUP_OR)
	{
		if (shell->last_job_state & SUCCEDED)
			return (FALSE);
	}
	return (TRUE);
}

#include		<stdio.h>
void			run_job(void *context, void *data)
{
	t_registry	*shell;
	t_job		*job;
	t_process	*head;


	shell = context;
	job = data;
	printf("last_job %d");
	if (job == NULL || do_i_run(shell, job) == FALSE)
		return ;
	head = job->processes->data;
	//EXPAND ALL JOB
	if (job->processes->next == NULL)
		head->process_type |= IS_ALONE;
	else
		setup_pipe(job->processes);
	job->state = RUNNING;
	ft_lstiter_ctx(job->processes, shell, run_process);
	ft_lstremove_if(&job->processes, NULL, get_failed_process, del_process);
	waiter(job);
	shell->last_job_state = job->state;
	return ;
}

int8_t 			interpreter(t_registry *shell, t_list **cmd_group, uint32_t flag)
{
	static t_list	*job_lst;

	if (flag > 0)
	{
		ft_lstiter_ctx(job_lst, &flag, set_signaled);
		return (SUCCESS);
	}
	job_lst = ft_lstmap(*cmd_group, shell, group_to_job, del_group);
	ft_lstdel(cmd_group, del_group);
	load_signal_profile(EXEC_PROFILE);
	ft_lstiter_ctx(job_lst, shell, run_job);
	return (SUCCESS);
}
