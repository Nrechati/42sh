/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 15:44:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/06 15:13:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

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

static inline uint8_t visual_bounds_valid(t_interface *itf)
{
	if (itf->vis_start < 0
		|| itf->vis_stop < 0
		|| (uint64_t)itf->vis_start > vct_len(itf->line) + 1
		|| (uint64_t)itf->vis_stop > vct_len(itf->line) + 1)
		return (FALSE);
	return (TRUE);
}

void	redrawmode_visual(__unused t_registry *shell)
{
	t_interface *itf;

	if (visual_bounds_valid(&shell->interface) == FALSE)
		return ;
	itf = &shell->interface;
	if (itf->vis_stop < itf->vis_start)
		set_redraw_bounds(itf, itf->vis_stop, itf->vis_start + 2);
	else
		set_redraw_bounds(itf, itf->vis_start, itf->vis_stop + 2);

	redrawmode_line(shell);
	tputs(shell->interface.termcaps.standout_on, 1, &ft_putc);
	redrawmode_fptp(shell);
	tputs(shell->interface.termcaps.standout_off, 1, &ft_putc);
}
