/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:16:26 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/04 19:14:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

static inline char		*read_input_cmd(t_registry *shell)
{
	if (shell->option.option & COMMAND_OPT)
		return (ft_strdup(shell->option.command_str));
	return (read_input(STDIN_FILENO));
}

static void				batch_mode(t_registry *shell)
{
	char	*command;

	command = read_input_cmd(shell);
	if (ft_strcheck(command, ft_isprint) == TRUE)
		execution_pipeline(shell, command);
	else
		ft_dprintf(2, "21sh: Not a valid input.\n");
	ft_strdel(&command);
}

static inline uint8_t	is_shell_interactive(t_registry *shell)
{
	if ((shell->option.option & COMMAND_OPT) == FALSE
			&& isatty(STDIN_FILENO) != 0)
	{
		shell->option.option |= INTERACTIVE_OPT;
		return (TRUE);
	}
	return (FALSE);
}

void					launch_shell(t_registry *shell)
{
	uint64_t setup_flag;

	if (is_shell_interactive(shell) == TRUE)
	{
		setup_flag = setup_interface(shell);
		ft_dprintf(2, "|--> Interface setup returned %lu\n", setup_flag);

		if ((setup_flag & CRITICAL_ERROR) == FALSE)
			interactive_mode(shell);

		teardown_interface(shell);
	}
	else
		batch_mode(shell);
}
