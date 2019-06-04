/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_special_ak.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:20:05 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/04 17:20:30 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t		ak_hightab(t_registry *shell)
{
	if (shell->interface.visual_mode == TRUE)
		return (SUCCESS);
	return (SUCCESS);
}

int8_t		ak_delete(t_registry *shell)
{
	if (shell->interface.visual_mode == TRUE)
		return (FAILURE);

	vct_del_char(shell->interface.line, shell->interface.cursor.index);
	set_redraw_flags(&shell->interface, RD_LINE | RD_CMOVE);
//	set_redraw_bounds(&shell->interface,
//					shell->interface.cursor.index - 1, 0);
	set_cursor_pos(&shell->interface, shell->interface.cursor.index);
	return (SUCCESS);
}

int8_t		ak_backspace(t_registry *shell)
{
	if (shell->interface.visual_mode == TRUE)
		return (FAILURE);

	if (shell->interface.cursor.index == 0)
		return (FAILURE);
	vct_del_char(shell->interface.line, shell->interface.cursor.index - 1);

	set_redraw_flags(&shell->interface, RD_LINE | RD_CMOVE);
//	set_redraw_bounds(&shell->interface, shell->interface.cursor.index - 1,
//					vct_len(shell->interface.window.displayed_line) + 1);
	set_cursor_pos(&shell->interface, shell->interface.cursor.index - 1);
	return (SUCCESS);
}

int8_t		ak_ctrl_d(t_registry *shell)
{
	if (shell->interface.visual_mode == TRUE)
		return (SUCCESS);

	if (shell->interface.cursor.index == 0
			&& vct_len(shell->interface.line) == 0)
	{
		vct_add(shell->interface.line, 4);
		return (SUCCESS);
	}
	return (ak_delete(shell));
}

int8_t		ak_ctrl_l(t_registry *shell)
{
	if (shell->interface.visual_mode == TRUE)
		return (FAILURE);

	set_redraw_flags(&shell->interface, RD_CLEAR | RD_CEND);
	return (SUCCESS);
}
