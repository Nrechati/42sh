/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 15:39:38 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/29 15:21:17 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int8_t	run_current(t_registry *shell)
{
	t_job	*job;

	if (shell->current_plus != NULL)
		job = ((t_job*)(shell->current_plus)->data);
	else
	{
		ft_printf("42sh: bg: no current job\n");
		return (FAILURE);
	}
	jobctl(shell, job, JOBCTL_RUNINBG);
	return (SUCCESS);
}

uint8_t		bg_blt(t_registry *shell, char **av)
{
	t_job	*job;
	int8_t	result;
	uint8_t	ret;

	if (jobctl_is_active(shell) == FALSE)
		return (FAILURE);
	++av;
	if (*av == NULL)
		if (run_current(shell) == FAILURE)
			return (FAILURE);
	ret = SUCCESS;
	while (*av != NULL)
	{
		result = parse_jobid(&job, *av);
		if (result == FAILURE || result == BAD_PERCENTAGE
				|| (result == SUCCESS && shell->current_plus == NULL))
		{
			if (result == BAD_PERCENTAGE)
				ft_printf("bg: usage: bg [%%jobID]\n");
			else
				ft_printf("42sh: bg: %s: no such job\n", *av);
			ret = 1;
		}
		else
			jobctl(shell, job, JOBCTL_RUNINBG);
		++av;
	}
	return (ret);
}
