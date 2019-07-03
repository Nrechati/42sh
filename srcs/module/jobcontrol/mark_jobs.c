/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_jobs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:00:41 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/03 17:36:23 by skuppers         ###   ########.fr       */
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
		process->completed = TRUE;
		proclist = proclist->next;
	}
}

uint8_t	mark_proc_status(pid_t pid, int status)
{
	t_list		*joblist;
	t_job		*job;

//	ft_printf("pid:%d\n", pid);
	if (pid <= 0)
		return (42);
	joblist = g_shell->job_list;
	while (joblist != NULL)
	{
		job = joblist->data;
		if (WIFSTOPPED(status))
			mark_job_as_stopped(job);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) != 18 && WTERMSIG(status) != 19)
				mark_job_as_completed(job);
		}
		else if (WIFEXITED(status) == 1)
			mark_job_as_completed(job);
		joblist = joblist->next;
	}
	return (42);
}
