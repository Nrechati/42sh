/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:25:47 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/11 13:40:43 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <signal.h>

void			define_interface_signals(void)
{
	signal(SIGWINCH, interface_resize_handler);
//	signal(SIGINT, redraw_prompt);
}

void			define_default_signals(void)
{
	loop_signals(SIG_DFL);
}
