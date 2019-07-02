/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 10:33:09 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/02 15:30:44 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

int		check_redirect_error(void *context, void *data)
{
	t_process		*process;
	t_redirect		*redirect;

	process = context;
	redirect = data;
	if (redirect->type & FD_OPEN_ERROR)
		process->process_type = IS_OPEN_FAILED;
	if (redirect->type & FD_DUP_ERROR)
		process->process_type = IS_DUP_FAILED;
	if (redirect->type & FD_CRITICAL_ERROR)
	{
		ft_dprintf(2, SH_GENERAL_ERROR SH_MALLOC_ERROR);
		process->process_type = IS_CRITICAL;
	}
	if (redirect->type & FD_BAD_DESCRIPTOR)
	{
		ft_dprintf(2, SH_GENERAL_ERROR "%d: bad filedescriptor\n", redirect->to);
		process->process_type = IS_DUP_FAILED;
	}
	if (redirect->type & FD_AMBIGOUS_REDIRECT)
		process->process_type = IS_DUP_FAILED;
	if (process->process_type & (IS_DUP_FAILED | IS_CRITICAL | IS_OPEN_FAILED))
		return (FAILURE);
	return (SUCCESS);
}

void	set_ambigous_redirect(t_redirect *redirect, t_list *node)
{
	t_token		*token;

	token = node->data;
	ft_dprintf(2, SH_GENERAL_ERROR "%s: ambigous_redirect\n", token->data);
	redirect->type = FD_AMBIGOUS_REDIRECT;
}

int		redirect_or_other(__unused void *context, void *data)
{
	t_action		*action;

	action = data;
	if (action->type == A_ASSIGN)
		return (FALSE);
	return (TRUE);
}

void	close_redirect(void *data)
{
	t_redirect	*redirect;
	redirect = data;
	if (redirect->type & FD_REDIRECT)
	{
		if (redirect->to >= 3)
			close(redirect->to);
	}
}

void	del_process_redirect(void *data)
{
	t_process	*process;

	process = data;
	ft_lstiter(process->redirects, close_redirect);
}

void	do_redirect(void *data)
{
	t_redirect	*redirect;

	redirect = data;
	if (redirect->type & FD_PIPE_OUT)
		dup2(redirect->to, STDOUT_FILENO);
	else if (redirect->type & FD_PIPE_IN)
		dup2(redirect->to, STDIN_FILENO);
	else if (redirect->type & FD_DUP)
	{
		dup2(redirect->to, redirect->from);
		return;
	}
	else if (redirect->type & (FD_MOVE | FD_REDIRECT))
		dup2(redirect->to, redirect->from);
	else if (redirect->type & FD_CLOSE)
		close(redirect->from);
	else if (redirect->type & FD_CLOSE_SPECIAL)
	{
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
	if (redirect->type & (FD_PIPE_IN | FD_PIPE_OUT))
		close(redirect->from);
	close(redirect->to);
}
