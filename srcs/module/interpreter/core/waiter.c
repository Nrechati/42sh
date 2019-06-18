/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 10:31:56 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/18 17:53:55 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	update_pid(t_list *processes, pid_t pid, __unused int status)
{
	t_process	*current;

	while (processes)
	{
		current = processes->data;
		if (current->pid == pid)
		{
			if (WIFEXITED(status))
				current->completed = TRUE;
			if (WIFSIGNALED(status))
			{
				ft_printf("[1] - PID Kill by SIG%d\n", WTERMSIG(status)); //REWORK
				current->completed = TRUE; //Gestion Signaux
			}
		//	ft_dprintf(2, "\x1b[32m%s completed with success with PID %d\n\x1b[0m"
		//			, current->av[0]
		//			, pid);
			return ;
		}
		processes = processes->next;
	}
	return ;
}

uint8_t	all_is_done(t_list *processes)
{
	t_process	*current;

	while (processes)
	{
		current = processes->data;
		if (current->completed == FALSE)
			return (FALSE);
		processes = processes->next;
	}
//	ft_dprintf(2, "\x1b[32mAll is Done\n\x1b[0m");
	return (TRUE);
}

void	terminator(void *data)
{
	t_process	*process;

	process = data;
	if (process->completed == FALSE)
		kill(process->pid, SIGINT);
	return ;
}

int8_t	waiter(t_job *job)
{
	int		status;
	pid_t	pid;

//	ft_printf("\x1b[33mWaiter pgid: %d\n\x1b[0m", job->pgid);
	while (all_is_done(job->processes) == FALSE)
	{
		if (job->state & KILLED)
			ft_lstiter(job->processes, terminator);
		status = 0;
		pid = wait(&status);
		if (pid)
			update_pid(job->processes, pid, status);
	}
	job->state = ENDED;
	return (SUCCESS);
}
