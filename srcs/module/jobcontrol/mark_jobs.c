/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_jobs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:00:41 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/06 10:56:42 by nrechati         ###   ########.fr       */
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

void	mark_proc(pid_t pid, int status)
{
	t_job	*job;

	job = find_job(pid);
	if (pid <= 0 || job == NULL)
		return ;
	if (WIFSTOPPED(status))
	{
		ft_printf("stopped\n");
		mark_job_as_stopped(job);
	}
	else if (WIFEXITED(status) == 1)
	{
		ft_printf("exited\n");
		mark_job_as_completed(job);
	}
	else if (WIFSIGNALED(status))
	{
		ft_printf("signaled\n");
		if (WTERMSIG(status) != 18 && WTERMSIG(status) != 19)
		{
		ft_printf("termsig\n");
			mark_job_as_running(job);

		}
	}
}

uint8_t	mark_proc_status(void)
{
	t_job		*job;
	t_list		*joblst;
	pid_t		pid;
	int			status;

	joblst = g_shell->job_list;
	while (joblst != NULL)
	{
		job = joblst->data;
		pid = waitpid(job->pgid, &status, WNOHANG | WUNTRACED);
		mark_proc(pid, status);
		joblst = joblst->next;
	}
	return (42);
}
