/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:19:49 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/25 10:01:29 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_registry	*g_shell;

int8_t			shell_usage(void)
{
	ft_dprintf(2, "%s%s\nLong options:%s%s",
					SH42_USAGE_1,
					SH42_USAGE_2,
					SH42_USAGE_LONG_OPTION,
					SH42_USAGE_LONG_OPTION_2);
	return (FAILURE);
}

static void		init_log(t_registry *shell)
{
	init_debug_logger(shell);
	log_print(shell, LOG_INFO, "Options: \n");
	log_print(shell, LOG_INFO, "| h=%d | v=%d | d=%d |\n",
				(shell->option.option & HELP_OPT) == FALSE ? 0 : 1,
				(shell->option.option & DEBUG_OPT) == FALSE ? 0 : 1);
	log_print(shell, LOG_INFO, "| c=%d | cmd=%s |\n",
				(shell->option.option & COMMAND_OPT) == FALSE ? 0 : 1,
				shell->option.command_str);
}

static int8_t	init_shell(t_registry *shell, char **av, char **env)
{

	g_shell = shell;
	load_signal_profile(INIT_HANDLER);
	load_signal_profile(DFLT_PROFILE);
	ft_bzero(shell, sizeof(t_registry));
	if (set_environment(shell, av, env) == FAILURE)
		return (FAILURE);
	init_log(shell);
	term_mode(TERMMODE_INIT);
	return (SUCCESS);
}

int		main(int ac, char **av, char **env) // exit by shell_exit_routine
{
	t_registry		shell;


	(void)ac;
	if (init_shell(&shell, av + 1, env) == FAILURE)
		return (FAILURE);

	shell.pid = getpid();
	shell.active_jobs = 0;
	if (setpgid(shell.pid, shell.pid) < 0)
	{
		ft_dprintf(2, "Failed Setpgid\n");
		exit(-1);
	}
	tcsetpgrp(STDOUT_FILENO, shell.pid);
	g_shell = &shell;

	launch_shell(&shell);
	shell_exit_routine(&shell, SUCCESS);
	return (SUCCESS); // Never reaches this point
}
