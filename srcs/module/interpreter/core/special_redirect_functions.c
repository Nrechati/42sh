/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_redirect_functions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:23:24 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/02 20:30:01 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

static int	get_filename_special(t_list *node, char **file)
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

static void	set_filename_special(t_redirect *redirect, char *filename, int type)
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

void		stdout_truncate_special(t_redirect *redirect, t_action *action)
{
	char		*filename;
	int			open_flags;
	int			type;

	filename = NULL;
	open_flags = O_WRONLY | O_TRUNC | O_CREAT | O_CLOEXEC;
	if ((type = get_filename_special(action->data, &filename)) > 0)
		set_filename_special(redirect, filename, type);
	else if (type == FAILURE)
		redirect->type = FD_CRITICAL_ERROR;
	else if (*filename == '\0')
		set_ambigous_redirect(redirect, action->data);
	else
		open_write_file(redirect, filename, open_flags);
	ft_strdel(&filename);
}
