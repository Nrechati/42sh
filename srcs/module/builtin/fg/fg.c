/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:37:48 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/24 18:57:08 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t	fg_blt(__unused t_registry *shell, char **av)
{
	t_job	*job;

	++av;
	job = parse_jobid(*av);

	ft_printf("Parsejob returne job[%d] with process av |%s %s|\n",
					job->pgid, ((t_process*)job->processes->data)->av[0]);

	if (job == NULL && shell->current_plus != NULL)
		job = ((t_job *)shell->current_plus);
	if (job == NULL)
		ft_printf("fg: no current job.\n");
	else
	{
		ft_printf("Restoring pid [%d] to foreground.\n", job->pgid);
		jobctl(shell, job, JOBCTL_PUTINFG);
	}
	return (0);
}
