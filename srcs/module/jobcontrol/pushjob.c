/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushjob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:59:23 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/04 14:33:09 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void			push_current_job(t_registry *shell, t_list *job)
{
	char	*pgid;

	shell->current_minus = shell->current_plus;
	shell->current_plus = job;
	pgid = ft_itoa(((t_job*)job->data)->pgid);
	add_var(&shell->intern, "!", pgid, READONLY_VAR);
	ft_strdel(&pgid);
}

static void		set_minus(t_registry *shell, t_list *jobs)
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

void			pop_current_job(t_registry *shell, t_job *job)
{
	t_list	*jobs;

	jobs = NULL;
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
		set_minus(shell, jobs);
}
