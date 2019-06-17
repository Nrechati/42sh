/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_special_ak.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:20:05 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/17 17:19:55 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t		ak_ctrl_i(__unused t_registry *shell, __unused t_sle *sle)
{
//	sle->search_mode = TRUE;
//	sle->search_type = NEXT;
//	ft_bzero(sle->line->buffer, sle->line->size);
//	set_redraw_flags(sle, RD_LINE | RD_CEND);
	return (SUCCESS);
}

int8_t		ak_ctrl_r(__unused t_registry *shell, t_sle *sle)
{

	sle->search_mode = TRUE;
	sle->search_type = PREV;
	ft_bzero(sle->line->buffer, sle->line->size);
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	return (SUCCESS);
}

int8_t		ak_hightab(__unused t_registry *shell, t_sle *sle)
{
	if (sle->visual_mode == TRUE)
		return (FAILURE);
//	autocompletion(vct_get_string(sle->line), shell, ,);
	return (SUCCESS);
}

int8_t		ak_delete(__unused t_registry *shell, t_sle *sle)
{
	if (sle->visual_mode == TRUE)
		return (FAILURE);

	vct_del_char(sle->line, sle->cursor.index);
	set_redraw_flags(sle, RD_FPTE | RD_CMOVE);
	set_redraw_bounds(sle, sle->cursor.index - 1, 0);
	set_cursor_pos(sle, sle->cursor.index);
	return (SUCCESS);
}

int8_t		ak_backspace(__unused t_registry *shell, t_sle *sle)
{
	if (sle->visual_mode == TRUE)
		return (FAILURE);
	if (sle->search_mode == TRUE)
	{
		vct_pop(sle->sub_line);
		set_redraw_flags(sle, RD_LINE | RD_CEND);
		return (SUCCESS);
	}
	if (sle->cursor.index == 0)
		return (FAILURE);
	vct_del_char(sle->line, sle->cursor.index - 1);

	set_redraw_flags(sle, RD_FPTE | RD_CMOVE);
	set_redraw_bounds(sle, sle->cursor.index - 1,
					vct_len(sle->window.displayed_line) + 1);
	set_cursor_pos(sle, sle->cursor.index - 1);
	return (SUCCESS);
}

int8_t		ak_ctrl_d(__unused t_registry *shell, t_sle *sle)
{
	if (sle->visual_mode == TRUE)
		return (FAILURE);

	if (sle->cursor.index == 0
			&& vct_len(sle->line) == 0)
	{
		vct_add(sle->line, 4);
		return (SUCCESS);
	}
	return (ak_delete(shell, sle));
}

int8_t		ak_ctrl_l(__unused t_registry *shell, t_sle *sle)
{
	if (sle->visual_mode == TRUE)
		return (FAILURE);

	set_redraw_flags(sle, RD_CLEAR | RD_CEND);
	return (SUCCESS);
}
