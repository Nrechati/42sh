/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 10:33:09 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/11 12:13:10 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

int			redirect_or_other(void *action, __unused void *data)
{
	enum e_actions		type;

	type = ((t_action *)action)->action;
	if (type == A_ASSIGN)
		return (FALSE);
	return (TRUE);
}

void		del_redirects(void *data)
{
	t_redirect	*redirect;

	redirect = data;
	close_redirects(redirect);
	ft_free(redirect->file);
}

void		close_redirects(void *data)
{
	t_redirect	*redirect;

	redirect = data;
	if (redirect->type & FD_PIPE_OUT || redirect->type & FD_PIPE_IN)
		close(redirect->to);
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
	else if (redirect->type & FD_CLOSE)
		close(redirect->to);
}
