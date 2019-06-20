/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:42:30 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/20 10:44:10 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void		do_nofork_redirect(void *context, void *data)
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

static void		run_process(void *context, void *data)
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

static void		run_job(void *context, void *data)
{
	char		*job_type;
	t_job		*job;
	t_process	*head;
	t_registry	*shell;

	shell = context;
	job = data;
	job_type = ft_itoa(job->job_type);
	if (job == NULL || do_i_run(shell, ft_atoi(get_var(shell->intern, "job_type"))) == FALSE)
	{
		add_var(&shell->intern, "job_type", job_type, SET_VAR);
		return;
	}
	add_var(&shell->intern, "job_type", job_type, SET_VAR);
	head = job->processes->data;
	//EXPAND ALL JOB
	if (job->processes->next == NULL)
		head->process_type |= IS_ALONE;
	else
		setup_pipe(job->processes);
	job->state |= RUNNING;
	ft_lstiter_ctx(job->processes, shell, run_process);
	ft_lstremove_if(&job->processes, NULL, get_failed_process, del_process);
	waiter(shell, job);
	return ;
}

int8_t 			interpreter(t_registry *shell, t_list **cmd_group, int flag)
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
	add_var(&shell->intern, "job_type", "0", SET_VAR);
	return (SUCCESS);
}
