/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 15:39:38 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/06 17:52:50 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int8_t		run_current(t_registry *shell)
{
	t_job	*job;

	if (shell->current_plus != NULL)
		job = ((t_job*)(shell->current_plus)->data);
	else
	{
		ft_dprintf(2, "42sh: bg: no current job\n");
		return (FAILURE);
	}
	if (job->state == RUNNING)
	{
		ft_dprintf(2, "42sh: bg: job %d is already in background\n", job->id);
		return (FAILURE);
	}
	jobctl(shell, job, JOBCTL_RUNINBG);
	return (SUCCESS);
}

static	uint8_t		check_failure(t_registry *shell, char *av, int8_t result)
{
	if (result == FAILURE || result == BAD_PERCENTAGE
			|| (result == SUCCESS && shell->current_plus == NULL))
	{
		if (result == BAD_PERCENTAGE)
			ft_dprintf(2, "bg: usage: bg [%%jobID]\n");
		else
			ft_dprintf(2, "42sh: bg: %s: no such job\n", av);
		return (TRUE);
	}
	return (FALSE);
}

int8_t				bg_blt(t_registry *shell, char **av)
{
	t_job	*job;
	int8_t	result;
	uint8_t	ret;

	if (jobctl_is_active(shell) == FALSE
			|| am_i_forked(shell, "bg") == TRUE)
		return (FAILURE);
	++av;
	if (*av == NULL)
		if (run_current(shell) == FAILURE)
			return (FAILURE);
	ret = SUCCESS;
	while (*av != NULL)
	{
		result = parse_jobid(&job, *av);
		if (check_failure(shell, *av, result) == TRUE)
			ret = 1;
		else
			jobctl(shell, job, JOBCTL_RUNINBG);
		++av;
	}
	return (ret);
}
