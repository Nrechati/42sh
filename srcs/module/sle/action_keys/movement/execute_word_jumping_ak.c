/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_word_jumping_ak.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:22:09 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/04 17:22:14 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t		ak_ctrl_right(t_sle *sle)
{
	uint32_t		next_char;

	if (sle->cursor.index == vct_len(sle->line))
		return (FAILURE);
	next_char = 0;
	next_char = get_next_char(sle->line->buffer,
					          sle->cursor.index, 1);
	set_redraw_flags(sle, RD_NONE | RD_CMOVE);
	set_cursor_pos(sle, next_char);
	if (sle->visual_mode == TRUE)
		sle->vis_stop = next_char;
	return (SUCCESS);
}

int8_t		ak_ctrl_left(t_sle *sle)
{
	int32_t		next_char;

	if (sle->cursor.index == 0)
		return (FAILURE);
	next_char = 0;
	next_char = get_next_char(sle->line->buffer,
					          sle->cursor.index, - 1);
	set_redraw_flags(sle, RD_NONE | RD_CMOVE);
	set_cursor_pos(sle, next_char);
	if (sle->visual_mode == TRUE && next_char >= 0)
		sle->vis_stop = next_char;
	return (SUCCESS);
}

int8_t		ak_ctrl_down(t_sle *sle)
{
	set_redraw_flags(sle, RD_NONE | RD_CMOVE);
	set_cursor_pos(sle,
					sle->cursor.index
					+ sle->window.cols);
	if (sle->visual_mode == TRUE
		&& (sle->cursor.index + sle->window.cols
				<= vct_len(sle->line) + 2))
			sle->vis_stop = (sle->cursor.index
							+ sle->window.cols);
	return (SUCCESS);
}

int8_t		ak_ctrl_up(t_sle *sle)
{
	set_redraw_flags(sle, RD_NONE | RD_CMOVE);
	set_cursor_pos(sle,
					sle->cursor.index
					- sle->window.cols);
	if (sle->visual_mode == TRUE)
			sle->vis_stop = (sle->cursor.index
							- sle->window.cols);
	return (SUCCESS);
}
