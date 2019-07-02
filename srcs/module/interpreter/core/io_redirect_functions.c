/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:41:01 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/02 21:40:11 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

void	duplicate_fd(t_redirect *redirect, t_action *action)
{
	redirect->type = FD_DUP;
	redirect->from = get_io(action->data);
	redirect->to = get_io(action->data->next);
}

void	io_append(t_redirect *redirect, t_action *action)
{
	char		*filename;
	int			open_flags;

	filename = get_filename(action->data);
	if (filename == NULL)
		redirect->type = FD_CRITICAL_ERROR;
	else if (*filename == '\0')
		set_ambigous_redirect(redirect, action->data);
	else
	{
		open_flags = O_RDWR | O_APPEND | O_CREAT | O_CLOEXEC;
		if ((redirect->to = open(filename, open_flags, 0644)) == FAILURE)
		{
			ft_dprintf(2, SH_GENERAL_ERROR "open FAILED on %s\n", filename);
			redirect->type = FD_OPEN_ERROR;
		}
		else
			redirect->type = FD_REDIRECT;
		redirect->from = get_io(action->data->next);
	}
	ft_strdel(&filename);
}

void	io_truncate(t_redirect *redirect, t_action *action)
{
	char		*filename;
	int			open_flags;

	filename = get_filename(action->data);
	if (filename == NULL)
		redirect->type |= FD_CRITICAL_ERROR;
	else if (*filename == '\0')
		set_ambigous_redirect(redirect, action->data);
	else
	{
		open_flags = O_RDWR | O_TRUNC | O_CREAT;
		if ((redirect->to = open(filename, open_flags, 0644)) == FAILURE)
		{
			ft_dprintf(2, SH_GENERAL_ERROR "open FAILED on %s\n", filename);
			redirect->type = FD_OPEN_ERROR;
		}
		else
			redirect->type = FD_REDIRECT;
		redirect->from = get_io(action->data->next);
	}
	ft_strdel(&filename);
}

void	io_readfile(t_redirect *redirect, t_action *action)
{
	char		*filename;

	filename = get_filename(action->data);
	if (filename == NULL)
		redirect->type = FD_CRITICAL_ERROR;
	else if (*filename == '\0')
		set_ambigous_redirect(redirect, action->data);
	else
	{
		if ((redirect->to = open(filename, O_RDWR, 0644)) == -1)
		{
			ft_dprintf(2, SH_GENERAL_ERROR "open FAILED on %s\n", filename);
			redirect->type = FD_OPEN_ERROR;
		}
		else
			redirect->type = FD_REDIRECT;
		redirect->from = get_io(action->data->next);
	}
	ft_strdel(&filename);
}

void	io_readfd(t_redirect *redirect, t_action *action)
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
		if (action_type == A_DUP && write(fd, str, 0) == 0)
			redirect->type = FD_DUP;
		else if (action_type == A_MOVE)
			redirect->type = FD_MOVE;
		else if (action_type == A_CLOSE)
			redirect->type = FD_CLOSE;
		else
			redirect->type = FD_BAD_DESCRIPTOR;
		redirect->from = get_io(action->data->next);
	}
}
