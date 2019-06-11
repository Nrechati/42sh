/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bacth_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:16:26 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/11 14:51:32 by skuppers         ###   ########.fr       */
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
	ft_printf("Batch mode.\n");
	t_vector	*cmd;

	cmd = get_input_cmd(shell);
	if (cmd == NULL || ft_strcheck(vct_get_string(cmd), ft_isprint) == FALSE)
		ft_dprintf(2, "21sh: Not a valid input.\n");
	else
	{
		execution_pipeline(shell, cmd);
		vct_del(&cmd);
	}
}

