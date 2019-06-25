/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:37:48 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/25 16:02:41 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t	fg_blt(__unused t_registry *shell, char **av)
{
	t_job	*job;

	++av;
	job = parse_jobid(*av);

	if (job == NULL && shell->current_plus != NULL)
		job = ((t_job *)shell->current_plus->data);
	if (job == NULL)
		ft_printf("fg: no current job.\n");
	else
		jobctl(shell, job, JOBCTL_PUTINFG);
	return (0);
}
