/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 13:44:25 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/05 13:47:32 by cempassi         ###   ########.fr       */
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
	(*redirecter)[action->type](&redirect, action);
	node = ft_lstnew(&redirect, sizeof(t_redirect));
	return (node);
}

int			setup_redirect(t_process *process)
{
	t_list		*redirect;

	redirect = ft_lstmap(process->redirects, NULL, set_redirect, del_action);
	if (ft_lstiter_ctx(redirect, process, check_redirect_error) == FAILURE)
	{
		ft_lstdel(&redirect, del_action);
		ft_lstdel(&process->redirects, close_redirect);
		return (FAILURE);
	}
	process->redirects = redirect;
	return (SUCCESS);
}
