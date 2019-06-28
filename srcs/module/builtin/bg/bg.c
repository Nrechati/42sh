/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 15:39:38 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/27 21:35:52 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t	bg_blt(t_registry *shell, __unused char **av)
{
	t_job	*job;
	int8_t	result;

	++av;
	if (*av == NULL)
	{
		if (shell->current_plus != NULL)
			job = ((t_job*)(shell->current_plus)->data);
		else
		{
			ft_printf("bg: no current job.\n");
			return (FAILURE);
		}
		jobctl(shell, job, JOBCTL_RUNINBG);
	}
	while (*av != NULL)
	{
		result = parse_jobid(&job, *av);
		if (result == FAILURE || (result == SUCCESS && shell->current_plus == NULL))
			ft_printf("bg: %s: no such job.\n", *av);
		else
			jobctl(shell, job, JOBCTL_RUNINBG);
		++av;
	}
	return (SUCCESS);
}
