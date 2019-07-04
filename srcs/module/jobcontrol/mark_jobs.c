/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_jobs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:00:41 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/04 18:11:23 by skuppers         ###   ########.fr       */
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
	t_job		*job;

	if (pid <= 0)
		return (42);

	job = find_job(pid);

	if (job == NULL)
		return (42);

	if (WIFEXITED(status) == 1)
	{
		ft_printf("Job %d has exited\n", job->pgid);
		mark_job_as_completed(job);
	}
	if (WIFSTOPPED(status))
	{
		ft_printf("Job %d has been stopped\n", job->pgid);
		mark_job_as_stopped(job);
	}
	else if (WIFSIGNALED(status))
	{
		ft_printf("Job has been signaled %d\n", WTERMSIG(status));
		if (WTERMSIG(status) != 18 && WTERMSIG(status) != 19)
			mark_job_as_completed(job);
	}
	return (42);
}
