/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_he_ak.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:21:43 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/20 10:55:56 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t	ak_home(__unused t_registry *shell, t_sle *sle)
{
	int64_t	x;

	if (sle->state != STATE_STD && sle->state != STATE_VISUAL)
		return (FAILURE);
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

int8_t	ak_end(__unused t_registry *shell, t_sle *sle)
{
	int64_t x;

	if (sle->state != STATE_STD && sle->state != STATE_VISUAL)
		return (FAILURE);
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
