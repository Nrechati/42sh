/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 15:39:38 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/25 21:03:34 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t	bg_blt(t_registry *shell, __unused char **av)
{
	t_job	*job;
	int8_t	result;

	++av;
	while (av != NULL)
	{
		job = NULL;
		result = parse_jobid(&job, *av);

		if (result == FAILURE || (result == SUCCESS && shell->current_plus == NULL))
			ft_printf("bg: no such job.\n");
		else if (job == NULL && shell->current_plus != NULL)
			job = ((t_job*)(shell->current_plus)->data);
		jobctl(shell, job, JOBCTL_RUNINBG);
		++av;
	}
	return (0);
}
