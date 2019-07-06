/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:19:49 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/06 18:27:22 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t			shell_usage(void)
{
	ft_dprintf(2, "%s%s\nLong options:%s%s",
					SH42_USAGE_1,
					SH42_USAGE_2,
					SH42_USAGE_LONG_OPTION,
					SH42_USAGE_LONG_OPTION_2);
	return (FAILURE);
}

static int8_t	init_shell(t_registry *shell, char **av, char **env)
{
	g_shell = shell;
	load_signal_profile(DFLT_PROFILE);
	ft_bzero(shell, sizeof(t_registry));
	if (set_environment(shell, av, env) == FAILURE)
		return (FAILURE);
	shell->pid = 0;
	shell->active_jobs = 0;
	term_mode(TERMMODE_INIT);
	return (SUCCESS);
}

int				main(int ac, char **av, char **env)
{
	t_registry		shell;

	(void)ac;
	g_shell = &shell;
	if (init_shell(&shell, av + 1, env) == FAILURE)
		shell_exit_routine(&shell, FAILURE);
	launch_shell(&shell);
	shell_exit_routine(&shell, FAILURE);
	return (FAILURE);
}
