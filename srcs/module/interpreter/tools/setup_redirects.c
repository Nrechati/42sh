/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 13:44:25 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/07 06:13:06 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		print_redirect(void *content)
{
	char			*redirect_type;
	t_redirect		*redirect;

	redirect = content;
	if (redirect->type & FD_DUP)
		redirect_type = "FD_DUP";
	if (redirect->type & FD_MOVE)
		redirect_type = "FD_MOVE";
	if (redirect->type & FD_REDIRECT)
		redirect_type = "FD_REDIRECT";
	if (redirect->type & FD_CLOSE)
		redirect_type = "FD_CLOSE";
	if (redirect->type & FD_CLOSE_SPECIAL)
		redirect_type = "FD_CLOSE_SPECIAL";
	if (redirect->type & FD_PIPE_IN)
		redirect_type = "FD_PIPE_IN";
	if (redirect->type & FD_PIPE_OUT)
		redirect_type = "FD_PIPE_OUT";
	if (redirect->type & FD_OPEN_ERROR)
		redirect_type = "FD_OPEN_ERROR";
	if (redirect->type & FD_DUP_ERROR)
		redirect_type = "FD_DUP_ERROR";
	if (redirect->type & FD_CRITICAL_ERROR)
		redirect_type = "FD_CRITICAL_ERROR";
	if (redirect->type & FD_BAD_DESCRIPTOR)
		redirect_type = "FD_BAD_DESCRIPTOR";
	if (redirect->type & FD_AMBIGOUS_REDIRECT)
		redirect_type = "FD_AMBIGOUS_REDIRECT";
	ft_printf("type: %s | to: %ld | from: %ld\n"
			, redirect_type, redirect->to, redirect->from);
}

static void	*set_redirect(void *context, void *data)
{
	static t_redirection	*redirecter;
	t_list					*node;
	t_action				*action;
	t_redirect				redirect;

	(void)context;
	if (redirecter == NULL)
		redirecter = redirecter_init();
	action = data;
	ft_bzero(&redirect, sizeof(t_redirect));
	if ((*redirecter)[action->type](&redirect, action) == FAILURE)
		return (NULL);
	node = ft_lstnew(&redirect, sizeof(t_redirect));
	return (node);
}

int			setup_redirect(t_process *process)
{
	t_list		*redirect;

	redirect = ft_lstmap(process->redirects, NULL, set_redirect, close_redirect);
	if (process->redirects != NULL && redirect == NULL)
	{
		process->type = FD_OPEN_ERROR;
		ft_lstdel(&redirect, close_redirect);
		ft_lstdel(&process->redirects, del_action);
		return (FAILURE);
	}
	if (ft_lstiter_ctx(redirect, process, check_redirect_error) == FAILURE)
	{
		ft_lstdel(&redirect, close_redirect);
		ft_lstdel(&process->redirects, del_action);
		return (FAILURE);
	}
	ft_lstdel(&process->redirects, del_action);
	process->redirects = redirect;
	process->redirects = ft_lstmerge(&process->pipe, process->redirects);
	process->pipe = NULL;
	return (SUCCESS);
}
