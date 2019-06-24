/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 10:31:56 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/24 15:37:27 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"


static void		set_status(t_registry *shell, t_job *job,
						t_process *current, int status)
{
	char	*exit_status;

	exit_status = NULL;
	if (WIFSTOPPED(status))
	{

		job->state = STOPPED;
		job->signo = WSTOPSIG(status);
		current->stopped = TRUE;

		shell->active_jobs++;
		job->id = (shell->active_jobs);

		jobctl(shell, job, JOBCTL_PUTINBG);
	}
	if (WIFEXITED(status))
	{
		exit_status = ft_itoa(WEXITSTATUS(status)); //PROTECT ?
		if (WEXITSTATUS(status) != 0)
			current->completed = ERROR;
		else
			current->completed = TRUE;
		tcsetpgrp(STDOUT_FILENO, job->pgid);
	}
	if (WIFSIGNALED(status))
	{
		ft_printf("%s terminated with status %d by %d\n", current->av[0], status, WTERMSIG(status));
		exit_status = ft_itoa(WTERMSIG(status) + 128);
		current->stopped = TRUE;
	}
	add_var(&shell->intern, "?", exit_status, SET_VAR);
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

void			kill_process(void *context, void *data)
{
	uint32_t	*signo;
	t_process	*process;

	signo = context;
	process = data;
	if (process->completed == FALSE)
		kill(process->pid, *signo);
	return ;
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
		pid = waitpid(-1, &status, WNOHANG | WUNTRACED);
		if (pid)
			update_pid(shell, job, pid, status);
	}
	if (job->state & KILLED)
		ft_printf("\x1b[33m\n\t[1]\t%d job killed by : SIG%d\n\x1b[0m"
													, job->pgid
													, job->signo);
	job->state ^= (RUNNING | ENDED);

	tcsetpgrp(STDOUT_FILENO, g_shell->pid);
	ft_dprintf(3, "Attaching shell back to terminal\n");

	return (SUCCESS);
}
