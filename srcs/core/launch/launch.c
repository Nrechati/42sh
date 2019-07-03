/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:16:26 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/03 13:36:22 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

inline uint8_t	is_shell_interactive(t_registry *shell)
{
	if ((shell->option.option & COMMAND_OPT) == FALSE
			&& isatty(STDIN_FILENO) != 0)
	{
		shell->option.option |= INTERACTIVE_OPT;
		return (TRUE);
	}
	return (FALSE);
}

void			launch_shell(t_registry *shell)
{
	#ifndef NOEXEC
	if (isatty(STDOUT_FILENO) != 1)
	{
		ft_printf("42sh: stdout: bad file descriptor.\n");
		return ;
	}
	#endif
	if (is_shell_interactive(shell) == TRUE)
		interactive_mode(shell);
	else
		batch_mode(shell);
}
