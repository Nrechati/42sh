/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_special_ak.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:38:25 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/07 19:38:27 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t		ak_delete(t_registry *shell, t_sle *sle)
{
	(void)shell;
	if (sle->state != STATE_STD)
		return (FAILURE);
	vct_del_char(sle->line, sle->cursor.index);
	set_redraw_flags(sle, RD_LINE | RD_CMOVE);
	set_cursor_pos(sle, sle->cursor.index);
	find_multiline_coord(sle, 0);
	return (SUCCESS);
}

int8_t		ak_backspace(t_registry *shell, t_sle *sle)
{
	uint64_t	index;

	(void)shell;
	if (sle->state != STATE_STD)
		return (FAILURE);
	if (sle->cursor.index == 0)
		return (FAILURE);
	index = sle->cursor.index <= 0 ? 0 : sle->cursor.index - 1;
	vct_del_char(sle->line, index);
	set_redraw_flags(sle, RD_LINE | RD_CMOVE);
	set_cursor_pos(sle, index);
	find_multiline_coord(sle, -1);
	return (SUCCESS);
}

int8_t		ak_ctrl_d(t_registry *shell, t_sle *sle)
{
	(void)shell;
	if (sle->state != STATE_STD)
		return (FAILURE);
	if (sle->cursor.index == 0 && vct_len(sle->line) == 0)
	{
		vct_add(sle->line, 4);
		return (SUCCESS);
	}
	return (ak_delete(shell, sle));
}

int8_t		ak_ctrl_l(t_registry *shell, t_sle *sle)
{
	(void)shell;
	if (sle->state != STATE_STD)
		return (FAILURE);
	set_redraw_flags(sle, RD_CLEAR | RD_CEND);
	return (SUCCESS);
}
