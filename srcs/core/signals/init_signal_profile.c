/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal_profile.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 18:23:42 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/06 12:18:45 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void				loop_defaults(void)
{
	int			i;

	i = 1;
	while (i < NB_SIGNALS)
	{
		signal(i, SIG_DFL);
		++i;
	}
}

void					load_profile_dflt(void)
{
	loop_defaults();
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void					load_profile_sle(void)
{
	loop_defaults();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGINT, sigint_sle);
	signal(SIGWINCH, sigwinch_sle);
}

void					load_profile_exec(void)
{
	loop_defaults();
	signal(SIGQUIT, sigstop_exec);
	signal(SIGTERM, sigstop_exec);
	signal(SIGINT, sigstop_exec);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, sigchld_exec);
}
