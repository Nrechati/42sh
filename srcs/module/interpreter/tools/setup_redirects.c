/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 13:44:25 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/07 17:00:41 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

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

int			setup_redirect(t_process *proc)
{
	t_list		*redirect;

	redirect = ft_lstmap(proc->redirects, NULL, set_redirect, close_redirect);
	if (proc->redirects != NULL && redirect == NULL)
	{
		proc->type = FD_OPEN_ERROR;
		ft_lstdel(&redirect, close_redirect);
		ft_lstdel(&proc->redirects, del_action);
		return (FAILURE);
	}
	if (ft_lstiter_ctx(redirect, proc, check_redirect_error) == FAILURE)
	{
		ft_lstdel(&redirect, close_redirect);
		ft_lstdel(&proc->redirects, del_action);
		return (FAILURE);
	}
	ft_lstdel(&proc->redirects, del_action);
	proc->redirects = redirect;
	proc->redirects = ft_lstmerge(&proc->pipe, proc->redirects);
	proc->pipe = NULL;
	return (SUCCESS);
}
