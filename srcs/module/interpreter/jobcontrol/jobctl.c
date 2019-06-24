/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobctl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:17:58 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/24 19:37:01 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sh21.h"

static void			job_to_registry(t_registry *shell, t_job *job)
{
	t_list		*data;
	t_job		job_cpy;

	ft_bzero(&job_cpy, sizeof(t_job));
	ft_memcpy(&job_cpy, job, sizeof(t_job));
	job->processes = NULL;
	job->term_modes = NULL;
	data = ft_lstnew(&job_cpy, sizeof(t_job));
	ft_lstaddback(&shell->job_list, data);
	shell->current_minus = shell->current_plus;
	shell->current_plus = data;
}


void	job_to_foreground(t_registry *shell, t_job *job)
{
	job->state = RUNNING;
//	shell->active_jobs--;

//	ft_lstdel(&,);
	((t_process*)job->processes->data)->stopped = FALSE;

//	ft_dprintf("Attaching pid %d to terminal\n", job->pgid);

	tcsetpgrp(STDOUT_FILENO, job->pgid);

	killpg(job->pgid, SIGCONT);
	waiter(shell, job);
}

void	jobctl(__unused t_registry *shell, t_job *job, uint8_t flag)
{
	if (flag & JOBCTL_LIST)
		print_jobs(job, flag);

	else if (flag & JOBCTL_PUTINBG)
		job_to_registry(shell, job);

	else if (flag & JOBCTL_PUTINFG)
		job_to_foreground(shell, job);
}
