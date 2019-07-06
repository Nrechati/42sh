/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:28:43 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/04 20:02:19 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

uint8_t			jobctl_is_active(t_registry *shell)
{
	if (isatty(STDIN_FILENO) != 0
					|| ((shell->option.option & INTERACTIVE_OPT) == FALSE))
	{
		ft_printf("42sh: No job control.\n");
		return (FALSE);
	}
	return (TRUE);
}

t_job			*find_job(pid_t pgid)
{
	t_list *job;

	job = g_shell->job_list;
	while (job != NULL)
	{
		if (((t_job*)job->data)->pgid == pgid)
			return (job->data);
		job = job->next;
	}
	return (NULL);
}

uint8_t			job_is_stopped(t_job *job)
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

uint8_t			job_is_completed(t_job *job)
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
