/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notify_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:01:47 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 09:51:34 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void	pop_job(t_job *job)
{
	remove_job_from_list(&g_shell->job_list, job);
	pop_current_job(g_shell, job);
	g_shell->active_jobs--;
	del_job(job);
	free(job);
}

void		notify_job_info(t_list *joblst, char *info)
{
	t_job		*job;
	t_list		*to_del;
	t_list		*jobl;
	char		*command;

	jobl = joblst;
	while (jobl != NULL)
	{
		job = jobl->data;
		if (job != NULL && job_is_completed(job) == TRUE)
		{
			get_job_av(job, &command);
			ft_printf("[%d]%c %s \t %s\n", job->id, job->current, info,
							command);
			ft_strdel(&command);
			to_del = jobl;
			jobl = jobl->next;
			pop_job(job);
			continue ;
		}
		else
			jobl = jobl->next;
	}
	update_jobinfos(g_shell);
}
