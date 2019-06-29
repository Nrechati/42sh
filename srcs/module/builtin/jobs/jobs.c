/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 16:03:30 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/25 22:20:30 by skuppers         ###   ########.fr       */
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

void		jobs(t_registry *shell, t_job *job, t_option option)
{
	if (option & L_OPT)
		jobctl(shell, job, JOBCTL_LIST | JOBCTL_LONG);
	else if (option & P_OPT)
		jobctl(shell, job, JOBCTL_LIST | JOBCTL_ID);
	else
		jobctl(shell, job, JOBCTL_LIST);
}

uint8_t		jobs_blt(t_registry *shell, char **av)
{
	t_option	option;
	t_job		*job;
	int8_t		result;
	uint8_t		ret;

	++av;
	if ((option = set_options(&av, get_option_jobs)) == ERROR_OPT)
		return (2);
	ret = SUCCESS;
	if (*av == NULL)
		jobs(shell, NULL, option);
	else
	{
		while (*av != NULL)
		{
			result = parse_jobid(&job, *av);
			if (result == FAILURE)
			{
				ft_printf("jobs: %s: no such job.\n", *av);
				ret = 1;
				++av;
				continue ;
			}
			jobs(shell, job, option);
			++av;
		}
	}
	return (ret);
}
