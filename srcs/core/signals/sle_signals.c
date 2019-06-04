/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sle_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:44:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/04 18:44:24 by skuppers         ###   ########.fr       */
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
