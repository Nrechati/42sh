/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:54:34 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/12 17:58:40 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

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
			redirect->type |= FD_DUP;
		redirect->from = STDIN_FILENO;
	}
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
			redirect->type |= FD_DUP;
		redirect->from = STDOUT_FILENO;
	}
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
			redirect->type |= FD_DUP;
		redirect->from = STDOUT_FILENO;
	}
}
