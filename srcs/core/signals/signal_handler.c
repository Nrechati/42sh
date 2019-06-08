/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:25:47 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/08 10:39:31 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <signal.h>

void			define_ign_signals(void)
{
//	loop_signals(SIG_IGN);
}

void			define_analyzer_signals(void)
{
//	loop_signals(SIG_IGN);
	signal(SIGINT, stop_analysis);
}

void			define_execution_signals(void)
{
	signal(SIGINT, kill_process);
	signal(SIGQUIT, kill_process);
}

void			define_interface_signals(void)
{
	signal(SIGWINCH, interface_resize_handler);
//	signal(SIGINT, redraw_prompt);
}

void			define_default_signals(void)
{
	loop_signals(SIG_DFL);
}
