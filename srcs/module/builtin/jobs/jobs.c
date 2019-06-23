/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 16:03:30 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/23 16:56:46 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
/*
static t_option		get_option_jobs(char *s, t_option option)
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

static char			*get_jobs_options(char ***av, t_option *option)
{
	char	*editor;

	editor = NULL;

	if (*av == NULL)
		return (NULL);

	if (*option == ERROR_OPT)
		return (NULL);

	*option |= set_options(av, get_option_jobs);
	return (editor);
}

static t_job	*id_to_job(int64_t job_id)
{
	t_list 		*job_ptr;
	int64_t		index;

	index = 1;
	job_ptr = g_shell->job_list;
	while (index++ != job_id && job_ptr != NULL)
		job_ptr = job_ptr->next;
	if (job_ptr == NULL)
		return (NULL);
	return ((t_job*)job_ptr->data);
}
*/
int8_t		jobs_blt(__unused t_registry *shell, char **av)
{
	t_option	option;
//	int64_t		job_id;
	t_job		*job_to_display;

	++av;
	option = 0;
//	job_id = 0;

//	job_id = get_jobs_options(&av, &option);

//	if (option == ERROR_OPT)
//		return (FAILURE);

//	if (job_id != 0)
//		job_to_display = id_to_job(job_id);
//	else
		job_to_display = NULL;

	if (option & L_OPT)
		jobctl(shell, job_to_display, JOBCTL_LIST | JOBCTL_LONG);

	else if (option & P_OPT)
		jobctl(shell, job_to_display, JOBCTL_LIST | JOBCTL_ID);

	else
		jobctl(shell, job_to_display, JOBCTL_LIST | JOBCTL_LONG);

	return (SUCCESS);
}
