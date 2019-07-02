/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notify_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:01:47 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/02 16:03:13 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	notify_job_info(t_list *joblst, char *info)
{
	t_job		*job;
	t_list		*jobl;
	char		*command;

	jobl = joblst;
	while (jobl != NULL)
	{
		job = jobl->data;
		if (job_is_completed(job) == TRUE)
		{
			get_job_av(job, &command);
			ft_printf("[%d]+ %s \t %s\n", job->id, info, command);
			remove_job_from_list(&g_shell->job_list, job);
			g_shell->active_jobs--;
			update_jobinfos(g_shell);
			pop_current_job(g_shell, job);
			ft_strdel(&command);
		}
		jobl = jobl->next;
	}
}
