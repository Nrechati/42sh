/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 16:03:30 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/24 19:58:27 by skuppers         ###   ########.fr       */
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


int8_t		jobs_blt(t_registry *shell, char **av)
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
