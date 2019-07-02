/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_jobs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 10:07:40 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/02 14:09:23 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	push_current_job(t_registry *shell, t_list *job)
{
	shell->current_minus = shell->current_plus;
	shell->current_plus = job;
	add_var(&shell->intern, "!", ft_itoa(((t_job*)job->data)->pgid), READONLY_VAR);
}

void	pop_current_job(t_registry *shell, t_job *job)
{
	t_list	*jobs;

	if (shell->current_plus == NULL)
		return ;
	if ((t_job*)shell->current_plus->data == job)
	{
		shell->current_plus = shell->current_minus;
		jobs = shell->job_list;
		while (jobs != NULL)
		{
			if (jobs != shell->current_plus && jobs != NULL)
				shell->current_minus = jobs;
			jobs = jobs->next;
		}
	}
	else if ((t_job*)shell->current_minus->data == job)
	{
		jobs = shell->job_list;
		shell->current_minus = NULL;
		while (jobs != NULL)
		{
			if (jobs != shell->current_plus && jobs != NULL)
				shell->current_minus = jobs;
			jobs = jobs->next;
		}
	}
}

static void	update_current_job(t_registry *shell)
{
	t_list *jobs;

	jobs = shell->job_list;
	while (jobs != NULL)
	{
		if (g_shell->current_plus == jobs)
			((t_job*)jobs->data)->current = '+';
		else if (g_shell->current_minus == jobs)
			((t_job*)jobs->data)->current = '-';
		else
			((t_job*)jobs->data)->current = ' ';
		jobs = jobs->next;
	}
}

static void	update_job_ids(t_registry *shell)
{
	uint32_t	id;
	t_job		*job;
	t_list		*job_ptr;

	id = 1;
	job_ptr = shell->job_list;
	while (id <= shell->active_jobs && job_ptr != NULL)
	{
		job = job_ptr->data;
		job->id = id;
		++id;
		job_ptr = job_ptr->next;
	}
}

void	remove_done_jobs(t_registry *shell)
{
	t_job	*job;
	t_list	*job_ptr;

	job_ptr = shell->job_list;
	while (job_ptr != NULL)
	{
		job = (t_job*)job_ptr->data;
		if (job->state & ENDED)
			remove_job_from_list(&shell->job_list, job);
		job_ptr = job_ptr->next;
	}
}

int32_t mark_proc_status(pid_t pid, int status)
{
	t_list		*joblist;
	t_list		*proclist;
	t_job		*job;
	t_process	*process;

	if (pid > 0)
	{
		joblist = g_shell->job_list;
		while (joblist != NULL)
		{
			job = joblist->data;
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
			joblist = joblist->next;
		}
		return (0);
	}
	return (FAILURE);
}

void	update_jobinfos(t_registry *shell)
{
	int		status;
	pid_t 	pid;

	pid = waitpid(WAIT_ANY, &status, WNOHANG | WUNTRACED);
	mark_proc_status(pid, status);
	update_job_ids(shell);
	update_current_job(shell);
}
