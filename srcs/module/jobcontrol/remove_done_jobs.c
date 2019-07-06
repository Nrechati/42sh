/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_done_jobs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:00:09 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/06 10:25:31 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	remove_done_jobs(t_registry *shell)
{
	t_job	*job;
	t_list	*job_ptr;

	job_ptr = shell->job_list;
	while (job_ptr != NULL)
	{
		job = (t_job*)job_ptr->data;
		if (job_is_completed(job))
			remove_job_from_list(&shell->job_list, job);
		job_ptr = job_ptr->next;
	}
}
