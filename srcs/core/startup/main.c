/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:19:49 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/22 22:48:20 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_registry	*g_shell;

int8_t			shell_usage(void)
{
	ft_dprintf(2, "%s%s\nLong options:%s%s",
					SH21_USAGE_1,
					SH21_USAGE_2,
					SH21_USAGE_LONG_OPTION,
					SH21_USAGE_LONG_OPTION_2);
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

static int8_t	init_shell(t_registry *shell, char **arg, char **env)
{

	g_shell = shell;
	load_signal_profile(INIT_HANDLER);
	load_signal_profile(DFLT_PROFILE);
	ft_bzero(shell, sizeof(t_registry));
	if (set_environment(shell, arg, env) == FAILURE)
		return (FAILURE);
	init_log(shell);
	term_mode(TERMMODE_INIT);
	return (SUCCESS);
}

int		main(int ac, char **av, char **env) // exit by shell_exit_routine
{
	t_registry		shell;
	char			*expanded;

	(void)ac;
	g_shell = &shell;
	if (init_shell(&shell, av + 1, env) == FAILURE)
		shell_exit_routine(&shell, FAILURE);
	expanded =  expansion_pipeline(shell.intern, av[3]);
	ft_printf("Before expansion: %s \n After expansion : %s\n", av[3], expanded);
	exit(0);
/*	shell_pid = getpid();
	if (setpgid(shell_pid, shell_pid) < 0)
	{
		ft_dprintf(2, "Failed Setpgid\n");
		shell_exit_routine(&shell, FAILURE);
	}*/
	launch_shell(&shell);
	shell_exit_routine(&shell, SUCCESS);
	return (SUCCESS); // Never reaches this point
}
