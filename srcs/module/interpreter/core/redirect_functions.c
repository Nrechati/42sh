/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:54:34 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/06 17:06:15 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

int	move_fd(t_redirect *redirect, t_action *action)
{
	t_token		*token;

	token = action->data->data;
	redirect->from = ft_atoi(token->data);
	if ((redirect->to = get_io(action->data->next)) == FAILURE)
	{
		redirect->type = FD_BAD_DESCRIPTOR;
		return (FAILURE);
	}
	redirect->type = FD_MOVE;
	return (SUCCESS);
}

int	close_fd(t_redirect *redirect, t_action *action)
{
	if ((redirect->from = get_io(action->data)) == SUCCESS)
	{
		redirect->type = FD_CLOSE;
		return (SUCCESS);
	}
	redirect->type = FD_BAD_DESCRIPTOR;
	return (FAILURE);
}

int	open_read_file(t_redirect *redirect, char *filename, int flag, int from)
{
	if (access(filename, F_OK) == SUCCESS)
	{
		if (access(filename, R_OK) == FAILURE)
		{
			ft_dprintf(2, SH_GENERAL_ERROR "%s: permission denied\n", filename);
			redirect->type = FD_OPEN_ERROR;
			return (FAILURE);
		}
		if ((redirect->to = open(filename, flag, 0644)) == -1)
		{
			ft_dprintf(2, SH_GENERAL_ERROR "%s: open error\n", filename);
			redirect->type = FD_OPEN_ERROR;
			return (FAILURE);
		}
		else
			redirect->type = from;
		redirect->type = FD_REDIRECT;
		redirect->from = STDIN_FILENO;
		return (SUCCESS);
	}
	ft_dprintf(2, SH_GENERAL_ERROR "%s: no such file or directory\n", filename);
	redirect->type = FD_OPEN_ERROR;
	return (FAILURE);
}

int	stdin_readfile(t_redirect *redirect, t_action *action)
{
	char		*filename;
	int			open_flag;
	int			return_value;

	return_value = 0;
	filename = get_filename(action->data);
	open_flag = O_RDONLY | O_CLOEXEC;
	if (filename == NULL)
	{
		redirect->type = FD_CRITICAL_ERROR;
		return (FAILURE);
	}
	else if (*filename == '\0')
	{
		set_ambigous_redirect(redirect, action->data);
		return_value = FAILURE;
	}
	else
		return_value = open_read_file(redirect, filename, open_flag, 0);
	ft_strdel(&filename);
	return (return_value);
}

int	action_type(t_redirect *redirect, int action_type, char *str)
{
	int		fd;

	fd = ft_atoi(str);
	redirect->to = fd;
	if (action_type == A_DUP && write(fd, str, 0) == 0)
		redirect->type = FD_DUP;
	else if (action_type == A_MOVE)
		redirect->type = FD_MOVE;
	else if (action_type == A_CLOSE)
		redirect->type = FD_CLOSE;
	else
	{
		redirect->type = FD_BAD_DESCRIPTOR;
		return (FAILURE);
	}
	redirect->from = STDIN_FILENO;
	return (SUCCESS);
}

int	stdin_readfd(t_redirect *redirect, t_action *action)
{
	int		action_type_value;
	char	*str;
	int		return_value;

	str = NULL;
	return_value = 0;
	action_type_value = get_custom_fd(&str, action->data);
	if (action_type_value == FAILURE)
		redirect->type = FD_CRITICAL_ERROR;
	else if (action_type_value == -2)
	{
		redirect->type = FD_AMBIGOUS_REDIRECT;
		return_value = FAILURE;
	}
	else
		return_value = action_type(redirect, action_type_value, str);
	ft_strdel(&str);
	return (return_value);
}
