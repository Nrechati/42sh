/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:28:43 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/20 18:29:04 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sh21.h"

t_job	*find_job(t_list *joblist, pid_t pgid)
{
	t_list *job;

	job = joblist;
	while (job != NULL)
	{
		if (((t_job*)job->data)->pgid == pgid)
			return (job->data);
		job = job->next;
	}
	return (NULL);
}

uint8_t	job_is_stopped(t_job *job)
{
	t_list	*process;

	process = job->processes;
	while (process != NULL)
	{
		if (((t_process*)process->data)->completed == FALSE
				&& ((t_process*)process->data)->stopped == FALSE)
				return (FALSE);
		process = process->next;
	}
	return (TRUE);
}

uint8_t	job_is_completed(t_job *job)
{
	t_list	*process;

	process = job->processes;
	while (process != NULL)
	{
		if (((t_process*)process->data)->completed == FALSE)
				return (FALSE);
		process = process->next;
	}
	return (TRUE);

}
