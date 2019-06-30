/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   batch_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:16:26 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/30 10:08:44 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

static t_vector			*read_input(const int fd)
{
	char		buff[READ_SIZE + 1];
	t_vector	*cmd;
	int			ret;

	cmd = vct_new(0);
	while ((ret = read(fd, buff, READ_SIZE)) > 0)
	{
		buff[ret] = '\0';
		vct_scat(cmd, buff, ret);
	}
	if (ret == FAILURE)
	{
		vct_del(&cmd);
		return (NULL);
	}
	return (cmd);
}


static inline t_vector	*get_input_cmd(t_registry *shell)
{
	if (shell->option.option & COMMAND_OPT)
		return (vct_dups(shell->option.command_str));
	return (read_input(STDIN_FILENO));
}

void					batch_mode(t_registry *shell)
{
	t_vector	*cmd;

	cmd = get_input_cmd(shell);
	if (cmd == NULL || ft_strcheck(vct_get_string(cmd), ft_isprint) == FALSE)
		ft_putendl_fd("42sh: Not a valid input", 2);
	else
	{
		if (verif_line(NULL, cmd) == TRUE)
			execution_pipeline(shell, &cmd);
	}
}
