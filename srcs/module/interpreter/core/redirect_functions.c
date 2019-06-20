/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:54:34 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/20 03:53:50 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

void	close_fd(t_registry *shell, t_redirect *redirect, t_action *action)
{
	(void)shell;
	redirect->type |= FD_CLOSE;
	redirect->from = get_io(action->data);
}

void	stdin_readfile(t_registry *shell, t_redirect *redirect
					, t_action *action)
{
	char		*filename;

	(void)shell;
	filename = get_filename(action->data);

	if (filename == NULL)
		redirect->type |= FD_CRITICAL_ERROR;
	else
	{
		if ((redirect->to = open(filename, O_RDWR | O_CLOEXEC, 0766)) == -1)
		{
			ft_dprintf(2, SH_GENERAL_ERROR "open FAILED on %s\n", filename);
			redirect->type |= FD_OPEN_ERROR;
		}
		else
			redirect->type |= FD_REDIRECT;
		redirect->from = STDIN_FILENO;
	}
	ft_strdel(&filename);
}

void	stdout_append(t_registry *shell, t_redirect *redirect
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
		redirect->from = STDOUT_FILENO;
	}
	ft_strdel(&filename);
}

void	stdout_truncate(t_registry *shell, t_redirect *redirect
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
		if ((redirect->to = open(filename, open_flags, 0766)) == -1)
		{
			ft_dprintf(2, SH_GENERAL_ERROR "open FAILED on %s\n", filename);
			redirect->type |= FD_OPEN_ERROR;
		}
		else
			redirect->type |= FD_REDIRECT;
		redirect->from = STDOUT_FILENO;
	}
	ft_strdel(&filename);
}
