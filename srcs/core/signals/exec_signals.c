/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:41:13 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/15 11:40:26 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <signal.h>

void		stop_analysis(const int signo)
{
	(void)signo;
	g_shell->analyzer_signal = TRUE;
}

void		signal_analyzer(t_resolution *resolve)
{
	ft_dprintf(2, "42sh: Analyzer has been interrupted.\n");
	ft_lstdel(&resolve->tokens, del_token);
	ft_strdel(&resolve->token.data);
}

void		kill_process(const int signo)
{
	t_list		*proc;

	proc = NULL;
	(void)signo;
	while (proc != NULL)
	{
		kill(((t_process*)(proc->data))->pid, SIGINT);
		proc = proc->next;
	}
}

void		loop_signals(void (*func)(int))
{
	int signo;

	signo = 0;
	while (++signo < 32)
	{
		if (signo != SSIG_QUIT && signo != SSIG_STOP && signo != SSIG_KILL)
			signal(signo, func);
	}
}
