/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal_profile.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 18:23:42 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/15 18:44:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static struct sigaction	set_sigaction_struct(void (*handler)(int), int flags, sigset_t mask)
{
		struct sigaction sigaction;

		sigaction.sa_handler = handler;
		sigaction.sa_flags = flags;
		sigaction.sa_mask = mask;
		return (sigaction);
}

static void	loop_defaults(struct sigaction generic[NB_SIGNALS])
{
	int i;

	i = 1;
	while (i < NB_SIGNALS)
	{
		generic[i] = set_sigaction_struct(SIG_DFL, 0, 0);
		++i;
	}
}

void		init_tab_signal_dflt(struct sigaction tab_signal[NB_SIGNALS])
{
	struct sigaction ignore;

	loop_defaults(tab_signal);
	ignore = set_sigaction_struct(SIG_IGN, 0, 0);
	tab_signal[SIGINT] = ignore;
	tab_signal[SIGTERM] = ignore;
	tab_signal[SIGQUIT] = ignore;
	tab_signal[SIGTSTP] = ignore;
	tab_signal[SIGCONT] = ignore;
}

void		init_tab_signal_sle(struct sigaction tab_signal[NB_SIGNALS])
{
	loop_defaults(tab_signal);
	tab_signal[SIGQUIT] = set_sigaction_struct(SIG_IGN, 0, 0);
	tab_signal[SIGTERM] = set_sigaction_struct(sigterm_sle, 0, 0);
	tab_signal[SIGCONT] = set_sigaction_struct(sigcont_sle, 0, 0);
	tab_signal[SIGTSTP] = set_sigaction_struct(sigtstp_sle, 0, 0);
	tab_signal[SIGINT] = set_sigaction_struct(sigint_sle, 0, 0);
	tab_signal[SIGWINCH] = set_sigaction_struct(sigwinch_sle, 0, 0);
}

void		init_tab_signal_exec(struct sigaction tab_signal[NB_SIGNALS])
{
	struct sigaction ignore;

	loop_defaults(tab_signal);
	ignore = set_sigaction_struct(SIG_IGN, 0, 0);
	tab_signal[SIGINT] = set_sigaction_struct(sigint_exec, 0, 0);
	tab_signal[SIGILL] = set_sigaction_struct(sigill_exec, 0, 0);
	tab_signal[SIGTRAP] = set_sigaction_struct(sigtrap_exec, 0, 0);
	tab_signal[SIGABRT] = set_sigaction_struct(sigabrt_exec, 0, 0);
	tab_signal[SIGFPE] = set_sigaction_struct(sigfpe_exec, 0, 0);
	tab_signal[SIGBUS] = set_sigaction_struct(sigbus_exec, 0, 0);
	tab_signal[SIGSEGV] = set_sigaction_struct(sigsegv_exec, 0, 0);
	tab_signal[SIGSYS] = set_sigaction_struct(sigsys_exec, 0, 0);
	tab_signal[SIGQUIT] = set_sigaction_struct(sigquit_exec, 0, 0);
	tab_signal[SIGTERM] = set_sigaction_struct(sigterm_exec, 0, 0);
	tab_signal[SIGCONT] = set_sigaction_struct(sigcont_exec, 0, 0);
	tab_signal[SIGTSTP] = set_sigaction_struct(sigtstp_exec, 0, 0);
	tab_signal[SIGTTIN] = set_sigaction_struct(sigttin_exec, 0, 0);
	tab_signal[SIGTTOU] = set_sigaction_struct(sigttou_exec, 0, 0);
	tab_signal[SIGCHLD] = set_sigaction_struct(sigchld_exec, 0, 0);
}

