/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_word_jumping_ak.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:33:40 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/04 11:32:02 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"

int8_t		ak_ctrl_right(t_registry *shell)
{
	uint32_t		next_char;

	if (shell->interface.cursor.index == vct_len(shell->interface.line))
		return (FAILURE);
	next_char = 0;
	next_char = get_next_char(shell->interface.line->buffer,
					          shell->interface.cursor.index, 1);
	set_redraw_flags(&shell->interface, RD_NONE | RD_CMOVE);
	set_cursor_pos(&shell->interface, next_char);
	if (shell->interface.visual_mode == TRUE)
		shell->interface.vis_stop = next_char;
	return (SUCCESS);
}

int8_t		ak_ctrl_left(t_registry *shell)
{
	int32_t		next_char;

	if (shell->interface.cursor.index == 0)
		return (FAILURE);
	next_char = 0;
	next_char = get_next_char(shell->interface.line->buffer,
					          shell->interface.cursor.index, - 1);
	set_redraw_flags(&shell->interface, RD_NONE | RD_CMOVE);
	set_cursor_pos(&shell->interface, next_char);
	if (shell->interface.visual_mode == TRUE && next_char >= 0)
		shell->interface.vis_stop = next_char;
	return (SUCCESS);
}

int8_t		ak_ctrl_down(t_registry *shell)
{
	set_redraw_flags(&shell->interface, RD_NONE | RD_CMOVE);
	set_cursor_pos(&shell->interface,
					shell->interface.cursor.index
					+ shell->interface.window.cols);
	if (shell->interface.visual_mode == TRUE
		&& (shell->interface.cursor.index + shell->interface.window.cols
				<= vct_len(shell->interface.line) + 2))
			shell->interface.vis_stop = (shell->interface.cursor.index
							+ shell->interface.window.cols);
	return (SUCCESS);
}

int8_t		ak_ctrl_up(t_registry *shell)
{
	set_redraw_flags(&shell->interface, RD_NONE | RD_CMOVE);
	set_cursor_pos(&shell->interface,
					shell->interface.cursor.index
					- shell->interface.window.cols);
	if (shell->interface.visual_mode == TRUE)
			shell->interface.vis_stop = (shell->interface.cursor.index
							- shell->interface.window.cols);
	return (SUCCESS);
}
