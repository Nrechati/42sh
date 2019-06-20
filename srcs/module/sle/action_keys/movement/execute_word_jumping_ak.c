/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_word_jumping_ak.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:22:09 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/20 10:55:47 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t		ak_ctrl_right(__unused t_registry *shell, t_sle *sle)
{
	uint32_t		next_char;

	if (sle->state != STATE_STD && sle->state != STATE_VISUAL)
		return (FAILURE);
	if (sle->cursor.index == vct_len(sle->line))
		return (FAILURE);
	next_char = 0;
	next_char = get_next_char(sle->line->buffer,
					          sle->cursor.index, 1);
	set_redraw_flags(sle, RD_NONE | RD_CMOVE);
	set_cursor_pos(sle, next_char);
	if (sle->state == STATE_VISUAL)
		sle->vis_stop = next_char;
	return (SUCCESS);
}

int8_t		ak_ctrl_left(__unused t_registry *shell, t_sle *sle)
{
	int32_t		next_char;

	if (sle->state != STATE_STD && sle->state != STATE_VISUAL)
		return (FAILURE);
	if (sle->cursor.index == 0)
		return (FAILURE);
	next_char = 0;
	next_char = get_next_char(sle->line->buffer,
					          sle->cursor.index, - 1);
	set_redraw_flags(sle, RD_NONE | RD_CMOVE);
	set_cursor_pos(sle, next_char);
	if (sle->state == STATE_VISUAL && next_char >= 0)
		sle->vis_stop = next_char;
	return (SUCCESS);
}

int8_t		ak_ctrl_down(__unused t_registry *shell, t_sle *sle)
{
	if (sle->state != STATE_STD && sle->state != STATE_VISUAL)
		return (FAILURE);
	set_redraw_flags(sle, RD_NONE | RD_CMOVE);
	set_cursor_pos(sle,
					sle->cursor.index
					+ sle->window.cols);
	if (sle->state == STATE_VISUAL
		&& (sle->cursor.index + sle->window.cols <= vct_len(sle->line) + 2))
			sle->vis_stop = (sle->cursor.index + sle->window.cols);
	return (SUCCESS);
}

int8_t		ak_ctrl_up(__unused t_registry *shell, t_sle *sle)
{
	if (sle->state != STATE_STD && sle->state != STATE_VISUAL)
		return (FAILURE);
	set_redraw_flags(sle, RD_NONE | RD_CMOVE);
	set_cursor_pos(sle,
					sle->cursor.index
					- sle->window.cols);
	if (sle->state == STATE_VISUAL)
			sle->vis_stop = (sle->cursor.index - sle->window.cols);
	return (SUCCESS);
}
