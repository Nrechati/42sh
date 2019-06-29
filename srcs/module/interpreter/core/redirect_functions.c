/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:54:34 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/29 18:00:22 by cempassi         ###   ########.fr       */
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

void	open_file(t_redirect *redirect, char *filename, int flag)
{
	if ((redirect->to = open(filename, flag, 0644)) == -1)
	{
		ft_dprintf(2, SH_GENERAL_ERROR "open FAILED on %s\n", filename);
		redirect->type = FD_OPEN_ERROR;
	}
	else
		redirect->type = FD_REDIRECT;
	redirect->from = STDIN_FILENO;

}
void	stdin_readfile(t_registry *shell, t_redirect *redirect
		, t_action *action)
{
	char		*filename;

	(void)shell;
	filename = get_filename(action->data);
	if (filename == NULL)
		redirect->type = FD_CRITICAL_ERROR;
	else if (*filename == '\0')
		set_ambigous_redirect(redirect, action->data);
	else
	{
		//O_RDWR | O_CLOEXEC
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
	else if (*filename == '\0')
		set_ambigous_redirect(redirect, action->data);
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
	else if (*filename == '\0')
		set_ambigous_redirect(redirect, action->data);
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

int		get_filename_special(t_list *node, char **file)
{
	int			action_type;
	t_token		*token;
	char		*filename;

	token = node->data;
	if ((filename = expansion_pipeline(g_shell->intern, token->data)) == NULL)
		return (FAILURE);
	if ((action_type = define_io_dup_move(token)) != A_AMBIGOUS_REDIRECT)
		return (action_type);
	*file = filename;
	return (SUCCESS);
}

void	set_filename_special(t_redirect *redirect, char *filename, int type)
{
	redirect->to = ft_atoi(filename);
	redirect->from = STDOUT_FILENO;
	if (type == A_CLOSE)
		redirect->type = FD_CLOSE_SPECIAL;
	else if (type == A_MOVE)
		redirect->type = FD_MOVE;
	else
		redirect->type = FD_DUP;
}

void	stdout_truncate_special(t_registry *shell, t_redirect *redirect
		, t_action *action)
{
	char		*filename;
	int			open_flags;
	int			type;

	(void)shell;
	filename = NULL;
	if ((type = get_filename_special(action->data, &filename)) > 0)
		set_filename_special(redirect, filename, type);
	else if (type == FAILURE)
		redirect->type = FD_CRITICAL_ERROR;
	else if (*filename == '\0')
		set_ambigous_redirect(redirect, action->data);
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
