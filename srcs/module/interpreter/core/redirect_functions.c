/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:54:34 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/12 15:26:00 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

void		stdin_readfile(t_registry *shell, t_redirect *redirect
					, t_action *action)
{
	t_token		*token;
	char		*path;

	(void)shell;
	path = NULL;
	token = action->data->data;
	ft_asprintf(&path, "./%s", token->data);
	if (path == NULL)
		redirect->type |= FD_CRITICAL_ERROR;
	else
	{
		if ((redirect->to = open(path, O_RDWR, 0766)) == -1)
		{
			ft_dprintf(2, SH_GENERAL_ERROR "open FAILED on %s\n", path);
			redirect->type |= FD_OPEN_ERROR;
		}
		else
			redirect->type |= FD_DUP;
		redirect->from = STDIN_FILENO;
	}
}

void		stdout_append(t_registry *shell, t_redirect *redirect
					, t_action *action)
{
	t_token		*token;
	char		*path;

	(void)shell;
	path = NULL;
	token = action->data->data;
	ft_asprintf(&path, "./%s", token->data);
	if (path == NULL)
		redirect->type |= FD_CRITICAL_ERROR;
	else
	{
		if ((redirect->to = open(path, O_RDWR | O_APPEND | O_CREAT, 0766)) == -1)
		{
			ft_dprintf(2, SH_GENERAL_ERROR "open FAILED on %s\n", path);
			redirect->type |= FD_OPEN_ERROR;
		}
		else
			redirect->type |= FD_DUP;
		redirect->from = STDOUT_FILENO;
	}
}

void		stdout_truncate(t_registry *shell, t_redirect *redirect
					, t_action *action)
{
	t_token		*token;
	char		*path;

	(void)shell;
	path = NULL;
	token = action->data->data;
	ft_asprintf(&path, "./%s", token->data);
	if (path == NULL)
		redirect->type |= FD_CRITICAL_ERROR;
	else
	{
		if ((redirect->to = open(path, O_RDWR | O_TRUNC | O_CREAT, 0766)) == -1)
		{
			ft_dprintf(2, SH_GENERAL_ERROR "open FAILED on %s\n", path);
			redirect->type |= FD_OPEN_ERROR;
		}
		else
			redirect->type |= FD_DUP;
		redirect->from = STDOUT_FILENO;
	}
}
