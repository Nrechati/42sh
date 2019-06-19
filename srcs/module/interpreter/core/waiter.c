/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 10:31:56 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/19 17:22:55 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void update_pid(t_registry *shell, t_job *job, pid_t pid, int status)
{
	char			*exit_status;
	t_list			*processes;
	t_process		*current;

	exit_status = NULL;
	processes = job->processes;
	while (processes)
	{
		current = processes->data;
		if (current->pid == pid)
		{
			if (WIFEXITED(status))
			{
				exit_status = ft_itoa(WEXITSTATUS(status));
				if (WEXITSTATUS(status) != 0)
					current->completed = ERROR;
				else
					current->completed = TRUE;
			}
			if (WIFSIGNALED(status))
			{
				ft_printf("%s terminated with status %d by %d\n"
						, current->av[0], status, WTERMSIG(status));
				exit_status = ft_itoa(WTERMSIG(status) + 128);
				current->stopped = TRUE;
			}
			add_var(&shell->intern, "?", exit_status, SET_VAR);
			ft_free(exit_status);
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

void			terminator(void *context, void *data)
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
			ft_lstiter_ctx(job->processes, &job->signo, terminator);
		status = 0;
		pid = wait(&status);
		if (pid)
			update_pid(shell, job, pid, status);
	}
	if (job->state & KILLED)
		ft_printf("\x1b[33m\n [1]\tjob killed by : SIG%d\n\x1b[0m"
													, job->signo);
	job->state ^= (RUNNING | ENDED);
	return (SUCCESS);
}
