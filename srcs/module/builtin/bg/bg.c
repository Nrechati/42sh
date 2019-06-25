/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 15:39:38 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/25 14:16:06 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t	bg_blt(__unused t_registry *shell, __unused char **av)
{
	t_job	*job;

	++av;
	job = parse_jobid(*av);

	if (job != NULL)
		ft_printf("Parsejob returned job[%d] with process av\n",
						(job->pgid));
	else
		ft_printf("fg: getjobid returned NULL\n");

	if (job == NULL && shell->current_plus != NULL)
		job = ((t_job*)shell->current_plus->data);

	if (job == NULL)
		ft_printf("bg: no current job.\n");
	else
		jobctl(shell, job, JOBCTL_RUNINBG);
	return (0);
}
