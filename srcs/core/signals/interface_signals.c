/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:36:52 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/04 17:43:55 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void			interface_resize_handler(__unused const int signo)
{
	t_interface		*itf;

	itf = &g_shell->interface;
	update_window(g_shell);
	set_redraw_flags(itf, RD_CLEAR | RD_CEND);
	redraw(g_shell);
}
