/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 16:03:30 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/21 16:48:09 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		print_jobctl(void *data)
{
	t_job *job;

	job = data;
	ft_printf("[jobnb] state %s\n", ((t_process*)job->processes->data)->av);
}

int8_t		jobs_blt(t_registry *shell, __unused char **av)
{
//	t_option	option;

	ft_lstiter(shell->job_list, print_jobctl);
	return (SUCCESS);
}
