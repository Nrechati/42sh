/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_he_ak.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:40:04 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/07 19:40:06 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t	ak_home(t_registry *shell, t_sle *sle)
{
	int64_t	x;

	(void)shell;
	if (sle->state != STATE_STD && sle->state != STATE_VISUAL)
		return (FAILURE);
	if (sle->state == STATE_VISUAL)
		set_redraw_flags(sle, RD_LINE | RD_CHOME);
	else
		set_redraw_flags(sle, RD_NONE | RD_CHOME);
	set_cursor_pos(sle, 0);
	if (sle->state == STATE_VISUAL)
	{
		x = 0;
		while ((sle->cursor.index + x) >= 1)
			sle->vis_stop = (sle->cursor.index + --x);
	}
	return (SUCCESS);
}

int8_t	ak_end(t_registry *shell, t_sle *sle)
{
	int64_t x;

	(void)shell;
	if (sle->state != STATE_STD && sle->state != STATE_VISUAL)
		return (FAILURE);
	if (sle->state == STATE_VISUAL)
		set_redraw_flags(sle, RD_LINE | RD_CEND);
	else
		set_redraw_flags(sle, RD_NONE | RD_CEND);
	set_cursor_pos(sle, vct_len(sle->line));
	if (sle->state == STATE_VISUAL)
	{
		x = 0;
		while ((sle->cursor.index + x) < vct_len(sle->line))
			sle->vis_stop = (sle->cursor.index + ++x);
	}
	return (SUCCESS);
}
