/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:41:01 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/12 18:02:37 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>


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
			redirect->type |= FD_DUP;
		redirect->from = get_io(action->data->next);
	}
}

void		io_append(t_registry *shell, t_redirect *redirect
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
		redirect->from = get_io(action->data->next);
	}
}

void		io_truncate(t_registry *shell, t_redirect *redirect
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
		redirect->from = get_io(action->data->next);
	}
}
