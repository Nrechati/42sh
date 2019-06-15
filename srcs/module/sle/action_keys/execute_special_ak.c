/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_special_ak.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:20:05 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/15 11:05:30 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t		ak_ctrl_s(t_sle *sle)
{
	t_vector *text;

	if (sle->search_mode == TRUE)
		return (FAILURE);

	sle->search_mode = TRUE;
	text = vct_dups(REV_SEARCH);
	print_prompt_to_window(sle, text);

	set_redraw_flags(sle, RD_LINE | RD_CEND);

	return (SUCCESS);
}

int8_t		ak_ctrl_r(t_sle *sle)
{
	t_vector *text;

	if (sle->search_mode == TRUE)
		return (FAILURE);

	sle->search_mode = TRUE;
	text = vct_dups(INC_SEARCH);
	print_prompt_to_window(sle, text);

	set_redraw_flags(sle, RD_LINE | RD_CEND);

	return (SUCCESS);
}

int8_t		ak_hightab(t_sle *sle)
{
	if (sle->visual_mode == TRUE)
		return (FAILURE);
	return (SUCCESS);
}

int8_t		ak_delete(t_sle *sle)
{
	if (sle->visual_mode == TRUE)
		return (FAILURE);

	vct_del_char(sle->line, sle->cursor.index);
	set_redraw_flags(sle, RD_FPTE | RD_CMOVE);
	set_redraw_bounds(sle, sle->cursor.index - 1, 0);
	set_cursor_pos(sle, sle->cursor.index);
	return (SUCCESS);
}

int8_t		ak_backspace(t_sle *sle)
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

int8_t		ak_ctrl_d(t_sle *sle)
{
	if (sle->visual_mode == TRUE)
		return (FAILURE);

	if (sle->cursor.index == 0
			&& vct_len(sle->line) == 0)
	{
		vct_add(sle->line, 4);
		return (SUCCESS);
	}
	return (ak_delete(sle));
}

int8_t		ak_ctrl_l(t_sle *sle)
{
	if (sle->visual_mode == TRUE)
		return (FAILURE);

	set_redraw_flags(sle, RD_CLEAR | RD_CEND);
	return (SUCCESS);
}
