/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 16:03:30 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/24 16:04:36 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_option		get_option_jobs(char *s, t_option option)
{
	option = 0;
	while (*s)
	{
		if (*s == 'l')
			option |= L_OPT;
		else if (*s == 'p')
			option |= P_OPT;
		else
		{
			ft_dprintf(STDERR_FILENO,
					"42sh: jobs: -%c: invalid option\n", *s);
			ft_dprintf(STDERR_FILENO, "jobs: usage: jobs [-l|-p] [job_id]\n");
			return (ERROR_OPT);
		}
		s++;
	}
	return (option);
}

static t_job	*id_to_job(uint64_t job_id)
{
	t_list 		*job_ptr;

	ft_printf("No segv\n");
	job_ptr = g_shell->job_list;
	while (job_ptr != NULL)
	{
		if (((t_job*)job_ptr->data)->id == job_id)
			return ((t_job*)job_ptr->data);
		job_ptr = job_ptr->next;
	}
	ft_printf("No segv2\n");
	return (NULL);
}

t_job			*get_current_job(char c)
{
	if (c == '+')
		return (NULL);
	else
		return (NULL);
}

t_job			*parse_jobname(char *jobname)
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

t_job			*parse_jobid(char *param)
{
	uint32_t	job_id;

	if (param == NULL)
		return (NULL);
	if (*param == '%')
	{
		param++;
		if (ft_isnumeric(param))
		{
			job_id = ft_atoi(param);
			if (job_id != 0)
				return (id_to_job(job_id));
			else
				return (NULL);
		}
		else
		{
			if (*param == '-' || *param == '+')
				return (get_current_job(*param));
			else
				return (parse_jobname(param));
		}
	}
	return (NULL);
}

int8_t		jobs_blt(__unused t_registry *shell, char **av)
{
	t_option	option;
	t_job		*job_to_display;

	++av;
	option = 0;

	if ((option = set_options(&av, get_option_jobs)) == ERROR_OPT)
		return (FAILURE);

	job_to_display = parse_jobid(*av);

	if (option & L_OPT)
		jobctl(shell, job_to_display, JOBCTL_LIST | JOBCTL_LONG);
	else if (option & P_OPT)
		jobctl(shell, job_to_display, JOBCTL_LIST | JOBCTL_ID);
	else
		jobctl(shell, job_to_display, JOBCTL_LIST);
	return (SUCCESS);
}
