/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:42:30 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/02 12:32:58 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void			set_context(uint8_t *std, t_redirect *redirect)
{
	if (redirect->from == STDIN_FILENO)
		*std |= CLOSED_STDIN;
	if (redirect->from == STDOUT_FILENO)
		*std |= CLOSED_STDOUT;
	if (redirect->from == STDERR_FILENO)
		*std |= CLOSED_STDERR;
	if (redirect->type == FD_CLOSE_SPECIAL)
	{
		*std |= CLOSED_STDERR;
		*std |= CLOSED_STDOUT;
	}
}

static int		do_nofork_redirect(void *context, void *data)
{
	t_redirect	*redirect;

	redirect = data;
	set_context(context, data);
	if (redirect->type & FD_DUP)
		dup2(redirect->to, redirect->from);
	else if (redirect->type & (FD_MOVE | FD_REDIRECT))
	{
		dup2(redirect->to, redirect->from);
		close(redirect->to);
	}
	else if (redirect->type & FD_CLOSE)
		close(redirect->from);
	else if (redirect->type & FD_CLOSE_SPECIAL)
	{
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
	return (SUCCESS);
}

void			run_builtin(t_registry *shell, t_process *process,
					uint8_t foreground)
{
	char			*tty_name;
	char			*status;
	uint8_t			std;
	t_builtin		builtin;

	std = 0;

	if (foreground == TRUE)
	{
		if (tcgetpgrp(STDOUT_FILENO) != *process->pgid)
			tcsetpgrp(STDOUT_FILENO, *process->pgid);
	}

	tty_name = ttyname(STDIN_FILENO);
	if (process->process_type & IS_ALONE)
		ft_lstiter_ctx(process->redirects, &std, do_nofork_redirect);
	else
		ft_lstiter(process->redirects, do_redirect);

	builtin = ft_hmap_getdata(&shell->hash.blt, process->av[0]);
	process->status = builtin(shell, process->av);

	status = ft_itoa(process->status);
	if (process->process_type & IS_ALONE)
		default_io(std, tty_name);

	ft_lstiter(process->redirects, close_redirect);
	add_var(&shell->intern, "?", status, READONLY_VAR);

	process->completed = 1;
	ft_strdel(&status);
	return ;
}

int				run_process(t_registry *shell, t_process *process,
						uint8_t foreground)
{
	if (process->process_type & (IS_DUP_FAILED | IS_CRITICAL | IS_OPEN_FAILED))
		return (process->completed = FAILURE);

	if (expand_process(shell->intern, process) == FAILURE)
	{
		process->process_type = IS_EXP_ERROR;
		return (FAILURE);
	}
	if (get_process_type(shell, process) == FAILURE)
	{
		ft_dprintf(2, SH_GENERAL_ERROR SH_MALLOC_ERROR);
		return(FAILURE);
	}
	if (process->process_type & IS_NOTFOUND)
		ft_dprintf(2, SH_GENERAL_ERROR "%s" INTERPRETER_NOT_FOUND, process->av[0]);

	else if (process->process_type & IS_ASSIGN)
		process->completed = assign_intern(shell, &process->env);

	else if (process->process_type == (IS_ALONE | IS_BLT))
		run_builtin(shell, process, foreground);
	else
		fork_process(shell, process, foreground);
	return (SUCCESS);
}

static int		run_job(void *context, void *data)
{
	char		*job_type;
	t_job		*job;
	t_process	*head;
	t_registry	*shell;

	uint8_t		foreground;

	foreground = TRUE;

	shell = context;
	job = data;
	job_type = ft_itoa(job->job_type);
	if (job == NULL)
		return (FAILURE);
	if (do_i_run(shell, job
			, ft_atoi(get_var(shell->intern, "job_type"))) == FALSE)
	{
		add_var(&shell->intern, "job_type", job_type, READONLY_VAR);
		ft_strdel(&job_type);
		return (SUCCESS);
	}
	add_var(&shell->intern, "job_type", job_type, READONLY_VAR);
	ft_strdel(&job_type);
	head = job->processes->data;
	job->state |= RUNNING;

	if (job->job_type & GROUP_BG)
		foreground = FALSE;

	if (job->processes->next == NULL)
	{
		head->process_type |= IS_ALONE;
		run_process(shell, head, foreground);
	}
	else
		launch_pipeline(shell, job->processes, foreground);

	if ((job->job_type & GROUP_BG) == TRUE)
	{
		t_list		*data;
		t_job		job_cpy;

		shell->active_jobs++;
		job->id = shell->active_jobs;
		ft_bzero(&job_cpy, sizeof(t_job));
		ft_memcpy(&job_cpy, job, sizeof(t_job));
		data = ft_lstnew(&job_cpy, sizeof(t_job));
		ft_lstaddback(&shell->job_list, data);
		push_current_job(shell, data);
		ft_printf("[%d] %d\n", job->id, job->pgid);
		job->processes = NULL;
		job->term_modes = NULL;
	}

	ft_lstiter(job->processes, del_process_redirect);
	ft_lstremove_if(&job->processes, NULL, get_failed_process, del_process);

	if (foreground)
		waiter(shell, job);

	return (SUCCESS);
}

int8_t 			interpreter(t_registry *shell, t_list **cmd_group, int flag)
{
	static t_list	*job_lst;

	if (flag != 0)
	{
		if (flag == FREE_INTERPRETER)
			ft_lstdel(&job_lst, del_job);
		else
			ft_lstiter_ctx(job_lst, &flag, set_signaled);
		return (SUCCESS);
	}
	job_lst = ft_lstmap(*cmd_group, shell, group_to_job, del_group);
	ft_lstdel(cmd_group, del_group);
	load_signal_profile(EXEC_PROFILE);
	ft_lstiter_ctx(job_lst, shell, run_job);
	add_var(&shell->intern, "job_type", "0", READONLY_VAR);
	ft_lstdel(&job_lst, del_job);
	shell->sigint = 0;
	return (SUCCESS);
}
