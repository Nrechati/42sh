/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 15:44:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/19 14:24:48 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

int8_t	ak_enter_visual_mode(t_sle *sle)
{
	if (sle->state != STATE_STD)
		return (FAILURE);

	sle->state = STATE_VISUAL;

	sle->vis_start = sle->cursor.index;
	sle->vis_stop = sle->cursor.index;

	return (SUCCESS);
}

// ESCAPE
int8_t	ak_exit_modes(t_sle *sle)
{
	if (sle->state == STATE_SEARCH)
	{
		if (ft_strequ(vct_get_string(sle->search_line), "Failed") == TRUE)
			vct_reset(sle->search_line);
		sle->line = sle->search_line;
	}

	sle->state = STATE_STD;

	set_redraw_flags(sle, RD_LINE | RD_CEND);

	return (SUCCESS);
}

static inline uint8_t visual_bounds_valid(t_sle *sle)
{
	if (sle->vis_start < 0
		|| sle->vis_stop < 0
		|| (uint64_t)sle->vis_start > vct_len(sle->line) + 1
		|| (uint64_t)sle->vis_stop > vct_len(sle->line) + 1)
		return (FALSE);
	return (TRUE);
}

void	redrawmode_visual(t_sle *sle)
{
	if (visual_bounds_valid(sle) == FALSE)
		return ;

	if (sle->vis_stop < sle->vis_start)
		set_redraw_bounds(sle, sle->vis_stop, sle->vis_start + 2);
	else
		set_redraw_bounds(sle, sle->vis_start, sle->vis_stop + 1);

	redrawmode_line(sle);
	tputs(sle->termcaps.standout_on, 1, &ft_putc);
	redrawmode_fptp(sle);
	tputs(sle->termcaps.standout_off, 1, &ft_putc);
}
