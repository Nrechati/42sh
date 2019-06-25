/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:37:48 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/25 22:23:34 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t	fg_blt(__unused t_registry *shell, char **av)
{
	t_job	*job;
	int8_t	result;

	++av;
	job = NULL;
	result = 0;

	if (av != NULL)
		result = parse_jobid(&job, *av);

	if (result == FAILURE || (result == SUCCESS && shell->current_plus == NULL))
		ft_printf("fg: no current job.\n");
	else if (job == NULL && shell->current_plus != NULL)
		job = ((t_job *)(shell->current_plus)->data);
	jobctl(shell, job, JOBCTL_PUTINFG);
	return (0);
}
