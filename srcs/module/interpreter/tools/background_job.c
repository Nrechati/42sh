/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_job.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 21:24:13 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/29 22:11:04 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	run_background_job(t_registry *shell, t_job *job)
{
	if (job != NULL)
	{
		killpg(job->pgid, SIGTSTP);
		job->state = STOPPED;
		job->signo = SIGTSTP;
		shell->active_jobs++;
		job->id = (shell->active_jobs);
		jobctl(shell, job, JOBCTL_PUTINBG);
		jobctl(shell, job, JOBCTL_RUNINBG);
		tcsetpgrp(STDOUT_FILENO, shell->pid);
	}
}