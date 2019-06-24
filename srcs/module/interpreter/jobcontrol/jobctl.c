/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobctl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:17:58 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/24 16:04:35 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sh21.h"

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
	job->current = '+';
	ft_printf("Job with id %d has been added to %d total jobs.\n",
						job->id, shell->active_jobs);
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
			ft_printf("[%d] %c %s \t %s\n", job->id, job->current, state, command);

		ft_strdel(&state);
		ft_strdel(&command);

		job_ptr = job_ptr->next;
	}
}

void	print_jobs(__unused t_job *job,__unused uint8_t flag)
{
	if (job == NULL)
		print_joblist(flag);
	else
		print_jobinfo(job, flag);
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
