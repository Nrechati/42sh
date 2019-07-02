/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:36:20 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/02 16:36:56 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void		set_status(t_registry *shell, t_job *job,
						t_process *current, int status)
{
	int			signo;
	char		*exit_status;

	exit_status = NULL;
	if (WIFSTOPPED(status))
	{
		job->state = STOPPED;
		job->signo = WSTOPSIG(status);
		mark_job_as_stopped(job);
		shell->active_jobs++;
		job->id = (shell->active_jobs);
		jobctl(shell, job, JOBCTL_PUTINBG);
	}
	if (WIFEXITED(status))
	{
		exit_status = ft_itoa((uint8_t)WEXITSTATUS(status)); //PROTECT ?
		if (WEXITSTATUS(status) != 0)
			current->completed = ERROR;
		else
			current->completed = TRUE;
	}
	if (WIFSIGNALED(status))
	{
		signo = WTERMSIG(status);
		if (signo == 2 || signo == 3)
			sigstop_exec(signo);
		exit_status = ft_itoa((uint8_t)(signo + 128));
		mark_job_as_stopped(job);
		//ft_printf("SIGNALED by: %d\n", exit_status);
	}
	add_var(&shell->intern, "?", exit_status, READONLY_VAR);
	ft_strdel(&exit_status);
}

static void		update_pid(t_registry *shell, t_job *job, pid_t pid, int status)
{
	t_list			*processes;
	t_process		*current;

	processes = job->processes;
	while (processes)
	{
		current = processes->data;
		if (current->pid == pid)
		{
			set_status(shell, job, current, status);
			return ;
		}
		processes = processes->next;
	}
	return ;
}

static uint8_t	all_is_done(t_list *processes)
{
	t_process	*current;

	while (processes)
	{
		current = processes->data;
		if (current->completed == FALSE && current->stopped == FALSE)
			return (FALSE);
		processes = processes->next;
	}
	return (TRUE);
}

int			kill_process(void *context, void *data)
{
	uint32_t	*signo;
	t_process	*process;

	signo = context;
	process = data;
	if (process->completed == FALSE)
		kill(process->pid, *signo);
	return (SUCCESS);
}

int8_t			waiter(t_registry *shell, t_job *job)
{
	int				status;
	pid_t			pid;

	while (all_is_done(job->processes) == FALSE)
	{
		if (job->state & KILLED)
			ft_lstiter_ctx(job->processes, &job->signo, kill_process);
		status = 0;
		pid = waitpid(-1, &status, WUNTRACED);
		if (pid)
			update_pid(shell, job, pid, status);
	}
//	if (job->state & KILLED)
//		ft_printf("\x1b[33m\n\t[1]\t%d job killed by : SIG%d\n\x1b[0m"
//													, job->pgid
//													, job->signo);
	job->state ^= (RUNNING | ENDED);
	tcsetpgrp(STDOUT_FILENO, g_shell->pid);
	return (SUCCESS);
}
