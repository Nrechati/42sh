/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 13:44:25 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/07 20:46:12 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int			close_fd(t_redirect *redirect, t_action *action)
{
	redirect->from = get_io_noprotect(action->data);
	redirect->type = FD_CLOSE;
	return (SUCCESS);
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

	if (process->redirects == NULL)
		return (SUCCESS);
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
	process->redirects = ft_lstmerge(&process->pipe, redirect);
	process->pipe = NULL;
	return (SUCCESS);
}
