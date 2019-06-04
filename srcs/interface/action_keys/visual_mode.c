/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 15:44:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/04 11:25:26 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>
#include "interface_functions.h"

int8_t	ak_enter_visual_mode(t_registry *shell)
{
	shell->interface.visual_mode = TRUE;
	shell->interface.vis_start = shell->interface.cursor.index;
	shell->interface.vis_stop = shell->interface.cursor.index;
	return (SUCCESS);
}

int8_t	ak_exit_visual_mode(t_registry *shell)
{
	shell->interface.visual_mode = FALSE;
	set_redraw_flags(&shell->interface, RD_LINE | RD_CMOVE);
	set_cursor_pos(&shell->interface, shell->interface.cursor.index);
	return (SUCCESS);
}

void	redrawmode_visual(__unused t_registry *shell)
{
	if (shell->interface.vis_start < 0
		|| shell->interface.vis_stop < 0
		|| (uint64_t)shell->interface.vis_start > vct_len(shell->interface.line) + 1
		|| (uint64_t)shell->interface.vis_stop > vct_len(shell->interface.line) + 1)
		return ;

	if (shell->interface.vis_stop < shell->interface.vis_start)
		set_redraw_bounds(&shell->interface, shell->interface.vis_stop,
											shell->interface.vis_start + 2);
	else
		set_redraw_bounds(&shell->interface, shell->interface.vis_start,
											shell->interface.vis_stop + 2);
	redrawmode_line(shell);
	tputs(shell->interface.termcaps.standout_on, 1, &ft_putc);
	redrawmode_fptp(shell);
	tputs(shell->interface.termcaps.standout_off, 1, &ft_putc);
}
