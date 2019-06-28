/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:54:34 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/28 20:44:22 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

void		close_fd(t_registry *shell, t_redirect *redirect, t_action *action)
{
	(void)shell;
	redirect->type = FD_CLOSE;
	redirect->from = get_io(action->data);
}

void	stdin_readfile(t_registry *shell, t_redirect *redirect
					, t_action *action)
{
	char		*filename;

	(void)shell;
	filename = get_filename(action->data);
	if (filename == NULL)
		redirect->type = FD_CRITICAL_ERROR;
	else
	{
		if ((redirect->to = open(filename, O_RDWR | O_CLOEXEC, 0644)) == -1)
		{
			ft_dprintf(2, SH_GENERAL_ERROR "open FAILED on %s\n", filename);
			redirect->type = FD_OPEN_ERROR;
		}
		else
			redirect->type = FD_REDIRECT;
		redirect->from = STDIN_FILENO;
	}
	ft_strdel(&filename);
}

void	stdin_readfd(__unused t_registry *shell, t_redirect *redirect
					, t_action *action)
{
	int		action_type;
	int		fd;
	char	*str;

	str = NULL;
	action_type = get_custom_fd(&str, action->data);
	if (action_type == FAILURE)
		redirect->type = FD_CRITICAL_ERROR;
	else if (action_type == -2)
		redirect->type = FD_BAD_DESCRIPTOR;
	else
	{
		fd = ft_atoi(str);
		redirect->to = fd;
		if (action_type == A_DUP && write(fd, str, 0) == 0 )
			redirect->type = FD_DUP;
		else if (action_type == A_MOVE)
			redirect->type = FD_MOVE;
		else if (action_type == A_CLOSE)
			redirect->type = FD_CLOSE;
		else
			redirect->type = FD_BAD_DESCRIPTOR;
		redirect->from = STDIN_FILENO;
	}
}

void	stdout_append(t_registry *shell, t_redirect *redirect
					, t_action *action)
{
	char		*filename;
	int			open_flags;

	(void)shell;
	filename = get_filename(action->data);
	if (filename == NULL)
		redirect->type = FD_CRITICAL_ERROR;
	else
	{
		open_flags = O_RDWR | O_APPEND | O_CREAT | O_CLOEXEC;
		if ((redirect->to = open(filename, open_flags, 0644)) == -1)
		{
			ft_dprintf(2, SH_GENERAL_ERROR "open FAILED on %s\n", filename);
			redirect->type = FD_OPEN_ERROR;
		}
		else
			redirect->type = FD_REDIRECT;
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
		redirect->type = FD_CRITICAL_ERROR;
	else
	{
		open_flags = O_RDWR | O_TRUNC | O_CREAT | O_CLOEXEC;
		if ((redirect->to = open(filename, open_flags, 0644)) == -1)
		{
			ft_dprintf(2, SH_GENERAL_ERROR "open FAILED on %s\n", filename);
			redirect->type = FD_OPEN_ERROR;
		}
		else
			redirect->type = FD_REDIRECT;
		redirect->from = STDOUT_FILENO;
	}
	ft_strdel(&filename);
}
