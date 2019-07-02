/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 10:30:55 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/02 23:14:46 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	print_var_lst(void *data)
{
	t_variable *var;

	var = data;
	ft_printf("\x1b[33mVar = %s || Data = %s\n\x1b[0m", var->name, var->data);
}

void	print_process(void *data)
{
	t_process *process;

	process = data;
	ft_showtab(process->av);
	ft_putstr("\x1b[33m");
	ft_printf("process->type: %d | process->pid: %d | process->pgid: %d\n"
			, process->type, process->pid, *process->pgid);
	ft_putstr("\x1b[0m");
}

void	print_job(void *data)
{
	t_job *job;

	job = data;
	ft_printf("\x1b[33mpgid : %ld | job_type: %u\n\x1b[0m"
			, job->pgid
			, job->type);
}
