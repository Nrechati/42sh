/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobctl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:17:58 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/23 16:51:22 by skuppers         ###   ########.fr       */
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
	shell->active_jobs++;
}

//Format:		[id]-/+ status	\t					av[0]
//Long Format:	[id]-/+ [job_pid] status:signal \t	av[0]
static void	print_joblist(__unused uint8_t flag)
{
	t_list		*job_ptr;
	uint64_t	job_id;
	char		current;

	job_id = 1;
	job_ptr = g_shell->job_list;
	while (job_ptr != NULL)
	{
//		if (job_id == g_shell->active_jobs)
			current = '+';
//		else if (job_id == g_shell->active_jobs - 1)
//			current = '-';
//		else
//			current = ' ';

//		if (flag & JOBCTL_LONG)
			ft_printf("[%lu] %c %ld %d \t %s\n", job_id, current,
							((t_job*)job_ptr->data)->pgid,
							((t_job*)job_ptr->data)->state,
					((t_process*)((t_job*)job_ptr->data)->processes->data)->av[0]);

//		else if (flag & JOBCTL_ID)
//			ft_printf("%d\n", ((t_job*)job_ptr->data)->pgid);

//		else
//			ft_printf("[%lu] %c %d \t %s\n", job_id, current,
//							((t_job*)job_ptr->data)->state,
//					((t_process*)((t_job*)job_ptr->data)->processes->data)->av[0]);

		++job_id;
		job_ptr = job_ptr->next;
	}

}

void	print_jobs(__unused t_job *job,__unused uint8_t flag)
{
	if (job == NULL)
		print_joblist(flag);
//	else
//		print_jobinfo(job, flag);
}

void	save_job_to_bg(__unused t_list *joblist, __unused pid_t job_pgid)
{

}

void	jobctl(__unused t_registry *shell, t_job *job, uint8_t flag)
{
	if (flag & JOBCTL_LIST)
		print_jobs(job, flag);

	else if (flag & JOBCTL_PUTINBG)
		job_to_registry(shell, job);

	else if (flag & JOBCTL_PUTINFG)
		;

}
