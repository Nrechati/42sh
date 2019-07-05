/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:37:48 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/05 13:38:51 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t	fg_blt(t_registry *shell, char **av)
{
	t_job	*job;
	int8_t	result;
	uint8_t	ret;

	if (jobctl_is_active(shell) == FALSE)
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
