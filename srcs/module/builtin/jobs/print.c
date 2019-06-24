/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 17:59:16 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/24 18:10:12 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void state_to_str(uint8_t state, char **str)
{
	*str = ft_strnew(32);

	if (state == PENDING)
		ft_strcpy(*str, "Pending");
	else if (state == RUNNING)
		ft_strcpy(*str, "Running");
	else if (state == STOPPED)
		ft_strcpy(*str, "Stopped");
	else
		ft_strcpy(*str, "Unknown");
}

static void	av_to_str(t_process *process, char **str)
{
	uint32_t	avnb;

	avnb = 0;
	*str = ft_strnew(256);
	while (process->av[avnb] != NULL)
	{
		if (*str == NULL)
			ft_strcpy(*str, process->av[avnb]);
		else
		{
			ft_strcat(*str, " ");
			ft_strcat(*str, process->av[avnb]);
		}
		++avnb;
	}
}


static void	print_jobinfo(__unused t_job *job, uint8_t __unused flag)
{
	char		*state;
	char		*command;

	state_to_str(job->state, &state);
	av_to_str(((t_process*)job->processes->data), &command);
	if (flag & JOBCTL_LONG)
		ft_printf("[%d] %c %ld %s:%d \t %s\n", job->id, job->current,
						job->pgid, state, job->signo, command);
	else if (flag & JOBCTL_ID)
		ft_printf("%d\n", job->pgid);
	else
		ft_printf("[%d] %c %s \t %s\n", job->id, job->current, state, command);
	ft_strdel(&state);
	ft_strdel(&command);
}

static void	print_joblist(__unused uint8_t flag)
{
	char		*state;
	char		*command;
	t_list		*job_ptr;
	t_job		*job;

	job_ptr = g_shell->job_list;
	while (job_ptr != NULL)
	{
		state = NULL;
		command = NULL;
		job = ((t_job*)job_ptr->data);
		state_to_str(job->state, &state);
		av_to_str(((t_process*)job->processes->data), &command);
		if (flag & JOBCTL_LONG)
			ft_printf("[%d] %c %ld %s:%d \t %s\n", job->id, job->current,
							job->pgid, state, job->signo, command);
		else if (flag & JOBCTL_ID)
			ft_printf("%d\n", job->pgid);
		else
			ft_printf("[%d] %c %s \t %s\n", job->id, job->current,
							state, command);
		ft_strdel(&state);
		ft_strdel(&command);
		job_ptr = job_ptr->next;
	}
}

void	print_jobs(t_job *job, uint8_t flag)
{
	t_list	*job_ptr;

	job_ptr = g_shell->job_list;
	while (job_ptr != NULL)
	{
		if (g_shell->current_plus == job_ptr)
			((t_job*)job_ptr->data)->current = '+';
		else if (g_shell->current_minus == job_ptr)
			((t_job*)job_ptr->data)->current = '-';
		else
			((t_job*)job_ptr->data)->current = ' ';
		job_ptr = job_ptr->next;
	}
	if (job == NULL)
		print_joblist(flag);
	else
		print_jobinfo(job, flag);
}
