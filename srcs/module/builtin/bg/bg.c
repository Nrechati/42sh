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

uint8_t		bg_blt(t_registry *shell, __unused char **av)
{
	t_job	*job;
	int8_t	result;
	uint8_t	ret;

	++av;
	if (*av == NULL)
	{
		if (shell->current_plus != NULL)
			job = ((t_job*)(shell->current_plus)->data);
		else
		{
			ft_printf("42sh: bg: no current job\n");
			return (1);
		}
		jobctl(shell, job, JOBCTL_RUNINBG);
	}
	ret = SUCCESS;
	while (*av != NULL)
	{
		result = parse_jobid(&job, *av);
		if (result == FAILURE
				|| (result == SUCCESS && shell->current_plus == NULL))
		{
			ft_printf("42sh: bg: %s: no such job\n", *av);
			ret = 1;
		}
		else
			jobctl(shell, job, JOBCTL_RUNINBG);
		++av;
	}
	return (ret);
}