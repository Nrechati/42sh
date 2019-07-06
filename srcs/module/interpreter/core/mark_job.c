/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:08:17 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/06 15:08:19 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	mark_job_as_running(t_job *job)
{
	t_list		*proclist;
	t_process	*process;

	proclist = job->processes;
	while (proclist != NULL)
	{
		process = proclist->data;
		process->stopped = FALSE;
		process->completed = FALSE;
		proclist = proclist->next;
	}
}

void	mark_job_as_stopped(t_job *job)
{
	t_list		*proclist;
	t_process	*process;

	proclist = job->processes;
	while (proclist != NULL)
	{
		process = proclist->data;
		process->stopped = TRUE;
		process->completed = FALSE;
		proclist = proclist->next;
	}
}

void	mark_job_as_completed(t_job *job)
{
	t_list		*proclist;
	t_process	*process;

	proclist = job->processes;
	while (proclist != NULL)
	{
		process = proclist->data;
		process->stopped = FALSE;
		process->completed = TRUE;
		proclist = proclist->next;
	}
}
