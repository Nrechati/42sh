/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_job.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 21:24:13 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/27 21:43:25 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	run_background_job(t_registry *shell, t_job *job)
{
	if (job != NULL)
		jobctl(shell, job, JOBCTL_RUNINBG);
}
