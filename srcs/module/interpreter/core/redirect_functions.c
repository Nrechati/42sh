/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:54:34 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/05 14:46:17 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

void	move_fd(t_redirect *redirect, t_action *action)
{
	redirect->type = FD_MOVE;
	redirect->from = get_io(action->data);
	redirect->to = get_io(action->data->next);
}

void	close_fd(t_redirect *redirect, t_action *action)
{
	redirect->type = FD_CLOSE;
	redirect->from = get_io(action->data);
}

void	open_read_file(t_redirect *redirect, char *filename, int flag)
{
	if (access(filename, F_OK) == SUCCESS)
	{
		if (access(filename, R_OK) == FAILURE)
		{
			ft_dprintf(2, SH_GENERAL_ERROR "%s: permission denied\n", filename);
			redirect->type = FD_OPEN_ERROR;
			return ;
		}
		if ((redirect->to = open(filename, flag, 0644)) == -1)
		{
			ft_dprintf(2, SH_GENERAL_ERROR "%s: open error\n", filename);
			redirect->type = FD_OPEN_ERROR;
		}
		else
			redirect->type = FD_REDIRECT;
		redirect->from = STDIN_FILENO;
		return ;
	}
	ft_dprintf(2, SH_GENERAL_ERROR "%s: no such file or directory\n", filename);
	redirect->type = FD_OPEN_ERROR;
	return ;
}

void	stdin_readfile(t_redirect *redirect, t_action *action)
{
	char		*filename;
	int			open_flag;

	filename = get_filename(action->data);
	open_flag = O_RDONLY | O_CLOEXEC;
	if (filename == NULL)
		redirect->type = FD_CRITICAL_ERROR;
	else if (*filename == '\0')
		set_ambigous_redirect(redirect, action->data);
	else
		open_read_file(redirect, filename, open_flag);
	ft_strdel(&filename);
}

void	stdin_readfd(t_redirect *redirect, t_action *action)
{
	int		action_type;
	int		fd;
	char	*str;

	str = NULL;
	action_type = get_custom_fd(&str, action->data);
	if (action_type == FAILURE)
		redirect->type = FD_CRITICAL_ERROR;
	else if (action_type == -2)
		redirect->type = FD_AMBIGOUS_REDIRECT;
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
		redirect->from = STDIN_FILENO;
	}
	ft_strdel(&str);
}
