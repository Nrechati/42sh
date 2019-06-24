/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:37:48 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/24 16:13:30 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static t_job	*id_to_job(uint64_t job_id)
{
	t_list 		*job_ptr;

	job_ptr = g_shell->job_list;
	while (job_ptr != NULL)
	{
		if (((t_job*)job_ptr->data)->id == job_id)
			return ((t_job*)job_ptr->data);
		job_ptr = job_ptr->next;
	}
	return (NULL);
}

static t_job			*parse_jobname(char *jobname)
{
	uint32_t	i;
	t_list		*job_ptr;
	char		*jobav;

	i = 1;
	job_ptr = g_shell->job_list;
	while (job_ptr != NULL)
	{
		jobav = ((t_process*)((t_job*)job_ptr->data)->processes->data)->av[0];
		if (ft_strbeginswith(jobav, jobname) == TRUE)
			return ((t_job*)job_ptr->data);
		job_ptr = job_ptr->next;
	}
	return (NULL);
}

static t_job			*get_current_job(char c)
{
	if (c == '+')
		return (NULL);
	else
		return (NULL);
}

static t_job	*parse_jobid(char *param)
{
	uint32_t	job_id;

	if (param == NULL)
		return (NULL);
	if (*param != '%')
		return (NULL);
	param++;
	if (ft_isnumeric(param))
	{
		job_id = ft_atoi(param);
		if (job_id == 0)
			return (NULL);
		return (id_to_job(job_id));
	}
	else if (*param == '+' || *param == '-')
		return (get_current_job(*param));
	else
		return (parse_jobname(param));
}

int8_t	fg_blt(__unused t_registry *shell, char **av)
{
	t_job	*job;

	++av;
	job = parse_jobid(*av); // if null-> take current '+' job

	if (job == NULL)
		ft_printf("fg Current job\n");
	else
		ft_printf("Parsed job w/ pid: %d\n", job->pgid);

//	jobctl(shell, job, JOBCTL_PUTINFG);

	return (0);
}
