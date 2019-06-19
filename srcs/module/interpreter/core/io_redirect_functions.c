/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:41:01 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/19 21:49:11 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

void		move_fd(t_registry *shell, t_redirect *redirect, t_action *action)
{
	(void)shell;
	redirect->type |= FD_MOVE;
	redirect->from = get_io(action->data);;
	redirect->to = get_io(action->data->next);
}

void		duplicate_fd(t_registry *shell, t_redirect *redirect
					, t_action *action)
{
	(void)shell;
	redirect->type = FD_DUP;
	redirect->from = get_io(action->data);
	redirect->to = get_io(action->data->next);
}

void		io_readfile(t_registry *shell, t_redirect *redirect
					, t_action *action)
{
	char		*filename;

	(void)shell;
	filename = get_filename(action->data);
	if (filename == NULL)
		redirect->type |= FD_CRITICAL_ERROR;
	else
	{
		if ((redirect->to = open(filename, O_RDWR, 0766)) == -1)
		{
			ft_dprintf(2, SH_GENERAL_ERROR "open FAILED on %s\n", filename);
			redirect->type |= FD_OPEN_ERROR;
		}
		else
			redirect->type |= FD_REDIRECT;
		redirect->from = get_io(action->data->next);
	}
	ft_strdel(&filename);
}

void		io_append(t_registry *shell, t_redirect *redirect
					, t_action *action)
{
	char		*filename;
	int			open_flags;

	(void)shell;
	filename = get_filename(action->data);
	if (filename == NULL)
		redirect->type |= FD_CRITICAL_ERROR;
	else
	{
		open_flags = O_RDWR | O_APPEND | O_CREAT | O_CLOEXEC;
		if ((redirect->to = open(filename, open_flags, 0766)) == -1)
		{
			ft_dprintf(2, SH_GENERAL_ERROR "open FAILED on %s\n", filename);
			redirect->type |= FD_OPEN_ERROR;
		}
		else
			redirect->type |= FD_REDIRECT;
		redirect->from = get_io(action->data->next);
	}
	ft_strdel(&filename);
}

void		io_truncate(t_registry *shell, t_redirect *redirect
					, t_action *action)
{
	char		*filename;
	int			open_flags;

	(void)shell;
	filename = get_filename(action->data);
	if (filename == NULL)
		redirect->type |= FD_CRITICAL_ERROR;
	else
	{
		open_flags = O_RDWR | O_TRUNC | O_CREAT | O_CLOEXEC;
		if ((redirect->to = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0766)) == -1)
		{
			ft_dprintf(2, SH_GENERAL_ERROR "open FAILED on %s\n", filename);
			redirect->type |= FD_OPEN_ERROR;
		}
		else
			redirect->type |= FD_REDIRECT;
		redirect->from = get_io(action->data->next);
	}
	ft_strdel(&filename);
}
