/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:37:48 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/06 10:13:49 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static uint8_t	is_fg_forked(t_registry *shell)
{
	if (getpid() != shell->pid)
	{
		ft_printf("42sh: fg: No job control.\n");
		return (TRUE);
	}
	return (FALSE);
}

int8_t	fg_blt(t_registry *shell, char **av)
{
	t_job	*job;
	int8_t	result;
	uint8_t	ret;

	if (jobctl_is_active(shell) == FALSE
				|| is_fg_forked(shell) == TRUE)
		return (FAILURE);
	++av;
	job = NULL;
	result = 0;
	ret = SUCCESS;
	if (av != NULL)
		result = parse_jobid(&job, *av);
	if (result == BAD_PERCENTAGE || result == FAILURE
				|| (result == SUCCESS && shell->current_plus == NULL))
	{
		if (result == BAD_PERCENTAGE)
			ft_printf("fg: usage: fg [%%jobID]\n");
		ft_printf("42sh: fg: no current job\n");
		ret = 1;
	}
	else if (job == NULL && shell->current_plus != NULL)
		job = ((t_job *)(shell->current_plus)->data);
	jobctl(shell, job, JOBCTL_PUTINFG);
	return (ret);
}
