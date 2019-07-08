/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_job.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 21:24:13 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/05 15:23:28 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termios.h>

int		setup_background_job(t_job *job)
{
	t_job		job_cpy;
	t_list		*node;

//	tcgetattr(STDIN_FILENO, job->term_modes);
	ft_lstiter(job->processes, del_process_redirect);
	ft_lstremove_if(&job->processes, NULL, get_failed_process, del_process);
	if (job->processes == NULL)
		return (SUCCESS);
	g_shell->active_jobs++;
	job->id = g_shell->active_jobs;
	ft_bzero(&job_cpy, sizeof(t_job));
	ft_memcpy(&job_cpy, job, sizeof(t_job));
	node = ft_lstnew(&job_cpy, sizeof(t_job));
	ft_lstaddback(&g_shell->job_list, node);
	push_current_job(g_shell, node);
	ft_printf("[%d] %d\n", job->id, job->pgid);
	job->processes = NULL;
	job->term_modes = NULL;
	return (SUCCESS);
}

t_list	**ptr_to_job_lst(t_list **job_lst, uint8_t mode)
{
	static t_list		**saved = NULL;

	if (mode == SET_ADDR)
		saved = job_lst;
	else if (mode == GET_ADDR)
		return (saved);
	return (NULL);
}
