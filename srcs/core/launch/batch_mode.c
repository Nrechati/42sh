/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   batch_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:16:26 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/03 00:40:36 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

static void				read_input(t_registry *shell)
{
	t_vector	*cmd;
	char		*line;

	line = NULL;
	cmd = NULL;
	while (1)
	{
		get_next_line(STDIN_FILENO, &line);
		if (ft_strcheck(line, ft_isprint) == TRUE)
		{
			cmd = vct_dups(line);
			if (verif_line(NULL, cmd) == TRUE)
				execution_pipeline(shell, &cmd);
			vct_del(&cmd);
		}
		else if (line != NULL)
			ft_putendl_fd("42sh: Not a valid input", 2);
		///////////////////// CA DECONNNNNNNNNNE
		ft_strdel(&line);
	}
}

void					batch_mode(t_registry *shell)
{
	t_vector	*cmd;

	if (shell->option.option & COMMAND_OPT)
	{
		if (shell->option.command_str != NULL
				&& ft_strcheck(shell->option.command_str, ft_isprint) == TRUE)
		{
			cmd = vct_dups(shell->option.command_str);
			if (verif_line(NULL, cmd) == TRUE)
				execution_pipeline(shell, &cmd);
		}
		else
			ft_putendl_fd("42sh: Not a valid input", 2);
	}
	else
		read_input(shell);
}
