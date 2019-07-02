/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushjob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:59:23 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/02 15:59:57 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	push_current_job(t_registry *shell, t_list *job)
{
	shell->current_minus = shell->current_plus;
	shell->current_plus = job;
	add_var(&shell->intern, "!", ft_itoa(((t_job*)job->data)->pgid), READONLY_VAR);
}

void	pop_current_job(t_registry *shell, t_job *job)
{
	t_list	*jobs;

	if (shell->current_plus == NULL)
		return ;
	if ((t_job*)shell->current_plus->data == job)
	{
		shell->current_plus = shell->current_minus;
		jobs = shell->job_list;
		while (jobs != NULL)
		{
			if (jobs != shell->current_plus && jobs != NULL)
				shell->current_minus = jobs;
			jobs = jobs->next;
		}
	}
	else if ((t_job*)shell->current_minus->data == job)
	{
		jobs = shell->job_list;
		shell->current_minus = NULL;
		while (jobs != NULL)
		{
			if (jobs != shell->current_plus && jobs != NULL)
				shell->current_minus = jobs;
			jobs = jobs->next;
		}
	}
}