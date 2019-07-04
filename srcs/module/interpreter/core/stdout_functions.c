/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:28:18 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/04 11:32:34 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

void	open_write_file(t_redirect *redirect, char *filename, int flag)
{
	if (access(filename, F_OK) == SUCCESS)
	{
		if (access(filename, W_OK) == FAILURE)
		{
			ft_dprintf(2, "42sh: %s: permission denied\n", filename);
			redirect->type = FD_OPEN_ERROR;
			return ;
		}
	}
	if ((redirect->to = open(filename, flag, 0644)) == -1)
	{
		ft_dprintf(2, "42sh: %s: open error\n", filename);
		redirect->type = FD_OPEN_ERROR;
	}
	else
		redirect->type = FD_REDIRECT;
	redirect->from = STDOUT_FILENO;
}

void	stdout_append(t_redirect *redirect, t_action *action)
{
	char		*filename;
	int			open_flags;

	filename = get_filename(action->data);
	open_flags = O_WRONLY | O_APPEND | O_CREAT | O_CLOEXEC;
	if (filename == NULL)
		redirect->type = FD_CRITICAL_ERROR;
	else if (*filename == '\0')
		set_ambigous_redirect(redirect, action->data);
	else
		open_write_file(redirect, filename, open_flags);
	ft_strdel(&filename);
}

void	stdout_truncate(t_redirect *redirect, t_action *action)
{
	char		*filename;
	int			open_flags;

	filename = get_filename(action->data);
	open_flags = O_RDWR | O_TRUNC | O_CREAT | O_CLOEXEC;
	if (filename == NULL)
		redirect->type = FD_CRITICAL_ERROR;
	else if (*filename == '\0')
		set_ambigous_redirect(redirect, action->data);
	else
		open_write_file(redirect, filename, open_flags);
	ft_strdel(&filename);
}
