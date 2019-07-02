/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_jobs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:00:41 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/02 16:07:59 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void 	mark_job_as_stopped(t_job *job)
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

void 	mark_job_as_completed(t_job *job)
{
	t_list		*proclist;
	t_process	*process;

	proclist = job->processes;
	while (proclist != NULL)
	{
		process = proclist->data;
		process->completed = TRUE;
		proclist = proclist->next;
	}
}

uint8_t mark_proc_status(pid_t pid, int status)
{
	t_list		*joblist;
	t_list		*proclist;
	t_job		*job;
	t_process	*process;

	if (pid <= 0)
		return (42);
	joblist = g_shell->job_list;
	while (joblist != NULL)
	{
		job = joblist->data;
		if (job_is_stopped(job) == FALSE)
		{
			proclist = job->processes;
			while (proclist != NULL)
			{
				process = proclist->data;
				process->status = status;
				if (WIFSTOPPED(status))
					process->stopped = TRUE;
				else
					process->completed = TRUE;
				proclist = proclist->next;
			}
		}
		joblist = joblist->next;
	}
	return (42);
}
