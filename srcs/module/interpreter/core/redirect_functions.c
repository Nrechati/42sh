/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:54:34 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/20 10:27:03 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

t_redirection	*redirecter_init(void)
{
	static t_redirection	redirecter;

	redirecter[A_STDOUT_TRUNCATE_FILE] = stdout_truncate;
	redirecter[A_STDOUT_APPEND_FILE] = stdout_append;
	redirecter[A_STDIN_READ_FILE] = stdin_readfile;
	redirecter[A_IO_TRUNCATE_FILE] = io_truncate;
	redirecter[A_IO_APPEND_FILE] = io_append;
	redirecter[A_IO_READ_FILE] = io_readfile;
	redirecter[A_DUP] = duplicate_fd;
	redirecter[A_CLOSE] = close_fd;
	redirecter[A_MOVE] = move_fd;
	redirecter[A_HEREDOC] = heredoc;
	redirecter[A_HEREDOC_TRIM] = move_fd;
	redirecter[A_IO_HEREDOC] = move_fd;
	redirecter[A_IO_HEREDOC_TRIM] = move_fd;
	return (&redirecter);
}

void		close_fd(t_registry *shell, t_redirect *redirect, t_action *action)
{
	(void)shell;
	redirect->type |= FD_CLOSE;
	redirect->from = get_io(action->data);
}

void		stdin_readfile(t_registry *shell, t_redirect *redirect
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
		redirect->from = STDIN_FILENO;
	}
	ft_strdel(&filename);
}

void		stdout_append(t_registry *shell, t_redirect *redirect
					, t_action *action)
{
	char		*filename;

	(void)shell;
	filename = get_filename(action->data);
	if (filename == NULL)
		redirect->type |= FD_CRITICAL_ERROR;
	else
	{
		if ((redirect->to = open(filename, O_RDWR | O_APPEND | O_CREAT, 0766)) == -1)
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

void		stdout_truncate(t_registry *shell, t_redirect *redirect
					, t_action *action)
{
	char		*filename;

	(void)shell;
	filename = get_filename(action->data);
	if (filename == NULL)
		redirect->type |= FD_CRITICAL_ERROR;
	else
	{
		if ((redirect->to = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0766)) == -1)
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
