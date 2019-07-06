/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal_profile.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 18:23:42 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/06 11:36:22 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
/*
static struct sigaction	set_sigaction_struct(void (*handler)(int),
			int flags, sigset_t mask)
{
	struct sigaction	sigaction;

	sigaction.sa_handler = handler;
	sigaction.sa_flags = flags;
	sigaction.sa_mask = mask;
	return (sigaction);
}
*/
static void				loop_defaults(void)
{
	int			i;

	i = 1;
	while (i < NB_SIGNALS)
	{
//		generic[i] = set_sigaction_struct(SIG_DFL, SA_RESTART, sigset);
		signal(i, SIG_DFL);
		++i;
	}
}

void					init_tab_signal_dflt(void)
{
	loop_defaults();
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
}

void					load_profile_sle(void)
{
	sigset_t			sigset;

	loop_defaults();
	signal(SIGQUIT, SIG_IGN);

	tab_signal[SIGQUIT] = set_sigaction_struct(SIG_IGN, SA_RESTART, sigset);
	tab_signal[SIGTERM] = set_sigaction_struct(sigterm_sle, SA_RESTART,
								sigset);
	tab_signal[SIGCONT] = set_sigaction_struct(SIG_IGN, SA_RESTART, sigset);
	tab_signal[SIGTSTP] = set_sigaction_struct(sigtstp_exec, SA_RESTART,
								sigset);
	tab_signal[SIGTTIN] = set_sigaction_struct(sigttin_exec, SA_RESTART,
								sigset);
	tab_signal[SIGTTOU] = set_sigaction_struct(sigttin_exec, SA_RESTART,
								sigset);
	tab_signal[SIGINT] = set_sigaction_struct(sigint_sle, 0, sigset);
	tab_signal[SIGWINCH] = set_sigaction_struct(sigwinch_sle, SA_RESTART,
								sigset);
}

void					init_tab_signal_exec(
							struct sigaction tab_signal[NB_SIGNALS])
{
	sigset_t			sigset;

	ft_bzero(&sigset, sizeof(sigset_t));
	loop_defaults(tab_signal);
	tab_signal[SIGHUP] = set_sigaction_struct(SIG_DFL, SA_RESTART, sigset);
	tab_signal[SIGINT] = set_sigaction_struct(sigstop_exec, SA_RESTART, sigset);
	tab_signal[SIGQUIT] = set_sigaction_struct(sigstop_exec, SA_RESTART,
								sigset);
	tab_signal[SIGTERM] = set_sigaction_struct(sigstop_exec, SA_RESTART,
								sigset);
	tab_signal[SIGTSTP] = set_sigaction_struct(SIG_DFL, SA_RESTART, sigset);
	tab_signal[SIGCONT] = set_sigaction_struct(SIG_DFL, SA_RESTART, sigset);
	tab_signal[SIGTTIN] = set_sigaction_struct(SIG_IGN, SA_RESTART, sigset);
	tab_signal[SIGTTOU] = set_sigaction_struct(SIG_IGN, SA_RESTART, sigset);
	tab_signal[SIGCHLD] = set_sigaction_struct(sigchld_exec, SA_RESTART,
								sigset);
}
