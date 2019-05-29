/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itf_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <skuppers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:36:52 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/27 10:09:08 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>
#include <sys/ioctl.h>
#include <termcap.h>
#include "interface_functions.h"
/*
void			redraw_prompt(const int signo)
{
	t_interface *itf;

	(void)signo;
	itf = &g_shell->interface;
	tc_ak_end(g_shell);
	if (signo != ft_atoi(INT_MAGIC_NUMBER))
		print_words(itf, "\n");
	itf->cursor.x = 0;
	itf->cursor.y = 0;
	if (signo != ft_atoi(INT_MAGIC_NUMBER))
		ft_vctreset(itf->line);
	itf->hist_ptr = NULL;
	print_words(itf, get_intern_var(g_shell, itf->state));
	itf->cursor.index = 0;
}
*/
void			interface_resize_handler(__unused const int signo)
{
	t_interface		*itf;

	itf = &g_shell->interface;
	update_window(g_shell);
	set_redraw_flags(itf, RD_CLEAR | RD_CEND);
	redraw(g_shell);
}
