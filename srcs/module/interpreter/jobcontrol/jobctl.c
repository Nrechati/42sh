/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobctl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:17:58 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/25 20:54:22 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sh21.h"

static void			remove_job_from_active_list(t_list **list, t_job *job)
{
	t_list	*ptr;
	t_list	*job_ptr;

	if (job == NULL)
		return ;
	job_ptr = *list;

	while (job_ptr != NULL && (t_job*)job_ptr->data != job)
		job_ptr = job_ptr->next;

	if (job_ptr == *list)
		*list = (job_ptr->next);
	else
	{
		ptr = *list;
		while (ptr->next != NULL && ptr->next != job_ptr)
			ptr = ptr->next;
		ptr->next = ptr->next->next;
	}
}

void	update_currents(t_registry *shell, t_job *job)
{
	if (shell->job_list == NULL)
	{
		shell->current_minus = NULL;
		shell->current_plus = NULL;
	}
	else
	{
		if (job != (t_job*)shell->current_minus->data)
			shell->current_plus = shell->current_minus;
		for (t_list *job = shell->job_list; job != NULL; job = job->next)
			if (job != shell->current_plus && job != NULL)
				shell->current_minus = job;
	}
}

static void			job_to_registry(t_registry *shell, t_job *job)
{
	char		*avs;
	t_list		*data;
	t_job		job_cpy;

	avs = NULL;
	ft_bzero(&job_cpy, sizeof(t_job));
	ft_memcpy(&job_cpy, job, sizeof(t_job));
	get_job_av(job, &avs);
	ft_printf("[%d]+  Stopped(%d) \t %s\n", job->id,
					job->signo, avs);
	ft_strdel(&avs);
	job->processes = NULL;
	job->term_modes = NULL;
	data = ft_lstnew(&job_cpy, sizeof(t_job));
	ft_lstaddback(&shell->job_list, data);

	shell->current_minus = shell->current_plus;
	shell->current_plus = data;

}

void	update_job_ids(t_registry *shell)
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

void	job_to_foreground(t_registry *shell, t_job *job)
{
	char	*avs;

	if (job == NULL)
		return ;
	job->state = RUNNING;
	((t_process*)job->processes->data)->stopped = FALSE;

	remove_job_from_active_list(&shell->job_list, job);
	shell->active_jobs--;

	update_job_ids(shell);
	update_currents(shell, job);

	get_job_av(job, &avs);
	ft_printf("%s\n", avs);
	ft_strdel(&avs);
	tcsetpgrp(STDOUT_FILENO, job->pgid);
	killpg(job->pgid, SIGCONT);
	waiter(shell, job);
}

void	job_run_background(__unused t_registry *shell, t_job *job)
{
	if (job->state == STOPPED)
	{
		job->state = RUNNING;
		job->signo = SIGCONT;
		killpg(job->pgid, SIGCONT);
	}
}

void	jobctl(__unused t_registry *shell, t_job *job, uint8_t flag)
{
	if (flag & JOBCTL_LIST)
		print_jobs(job, flag);

	else if (flag & JOBCTL_PUTINBG)
		job_to_registry(shell, job);

	else if (flag & JOBCTL_PUTINFG)
		job_to_foreground(shell, job);

	else if (flag & JOBCTL_RUNINBG)
		job_run_background(shell, job);

}
