/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 10:33:09 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/14 14:56:55 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

void		check_redirect_error(void *context, void *data)
{
	t_process		*process;
	t_redirect		*redirect;

	process = context;
	redirect = data;
	if (redirect->type & FD_OPEN_ERROR)
		process->process_type |= IS_OPEN_FAILED;
	if (redirect->type & FD_DUP_ERROR)
		process->process_type |= IS_DUP_FAILED;
	if (redirect->type & FD_CRITICAL_ERROR)
	{
		ft_dprintf(2, SH_GENERAL_ERROR SH_MALLOC_ERROR);
		process->process_type |= IS_CRITICAL;
	}
}

int			redirect_or_other(__unused void *context, void *data)
{
	t_action		*action;

	action = data;
	if (action->type == A_ASSIGN)
		return (FALSE);
	return (TRUE);
}

void		del_redirects(void *data)
{
	t_redirect	*redirect;

	redirect = data;
	close_redirect(redirect);
	ft_free(redirect->file);
}

void		close_redirect(void *data)
{
	t_redirect	*redirect;

	redirect = data;
	if (redirect->type & FD_PIPE_OUT || redirect->type & FD_PIPE_IN)
		close(redirect->to);
	if (redirect->type & (FD_DUP | FD_MOVE | FD_REDIRECT))
	{
		if (redirect->from >= 3)
			close(redirect->from);
		if (redirect->to >= 3)
			close(redirect->to);
	}
}

void		do_redirect(void *data)
{
	t_redirect	*redirect;

	redirect = data;
	if (redirect->type & FD_PIPE_OUT)
	{
		dup2(redirect->to, STDOUT_FILENO);
		close(redirect->from);
	}
	else if (redirect->type & FD_PIPE_IN)
	{
		dup2(redirect->to, STDIN_FILENO);
		close(redirect->from);
	}
	else if (redirect->type & FD_DUP)
		dup2(redirect->to, redirect->from);
	else if (redirect->type & (FD_MOVE | FD_REDIRECT))
		dup2(redirect->to, redirect->from);
	else if (redirect->type & FD_CLOSE)
		close(redirect->from);
}
