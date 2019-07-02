/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_special_ak.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:20:05 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/02 20:07:31 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t		ak_ctrl_t(__unused t_registry *shell, __unused t_sle *sle)
{
	if (sle->state != STATE_STD && sle->state != STATE_REVSEARCH)
		return (FAILURE);
	sle->state = STATE_INCSEARCH;
	sle->search_type = NEXT;
	ft_bzero(sle->line->buffer, sle->line->size);
	ft_bzero(sle->sub_line->buffer, sle->sub_line->size);
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	return (SUCCESS);
}

int8_t		ak_ctrl_r(__unused t_registry *shell, t_sle *sle)
{
	if (sle->state != STATE_STD && sle->state != STATE_INCSEARCH)
		return (FAILURE);
	sle->state = STATE_REVSEARCH;
	sle->search_type = PREV;
	ft_bzero(sle->line->buffer, sle->line->size);
	ft_bzero(sle->sub_line->buffer, sle->sub_line->size);
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	return (SUCCESS);
}

int8_t		ak_hightab(__unused t_registry *shell, t_sle *sle)
{
	char		*ret_completion;
	char		*substring;

	if (sle->state != STATE_STD)
		return (FAILURE);
	ret_completion = NULL;
	substring = ft_strdup(vct_get_string(sle->line));
	if (substring != NULL && ft_strlen(substring) > sle->cursor.index)
		substring[sle->cursor.index] = '\0';
	if (autocompletion(substring, shell,
			&ret_completion, NEW_SEARCH) == NOT_FOUND)
	{
		ft_strdel(&substring);
		return (FAILURE);
	}
	if (ret_completion != NULL)
	{
		vct_insert_string(sle->line, ret_completion, sle->cursor.index);
		set_redraw_flags(sle, RD_LINE | RD_CMOVE);
		set_cursor_pos(sle, sle->cursor.index + ft_strlen(ret_completion));
		ft_strdel(&ret_completion);
		ft_strdel(&substring);
	}
	else
	{
		ft_putendl("");
		update_window(sle);
		print_prompt(shell, sle);
		set_redraw_flags(sle, RD_LINE | RD_CMOVE);
		set_cursor_pos(sle, sle->cursor.index + ft_strlen(substring));
		ft_strdel(&substring);
	}
	set_redraw_bounds(sle, sle->cursor.index == 0 ? 0
			: sle->cursor.index - 1, vct_len(sle->line));
	return (SUCCESS);
}

int8_t		ak_delete(__unused t_registry *shell, t_sle *sle)
{
	if (sle->state != STATE_STD)
		return (FAILURE);
	vct_del_char(sle->line, sle->cursor.index);
	set_redraw_flags(sle, RD_LINE | RD_CMOVE);
	set_cursor_pos(sle, sle->cursor.index);
	find_multiline_coord(sle, 0);
	return (SUCCESS);
}

int8_t		ak_backspace(__unused t_registry *shell, t_sle *sle)
{
	uint64_t	index;

	if (sle->state != STATE_STD && sle->state != STATE_REVSEARCH
			&& sle->state != STATE_INCSEARCH)
		return (FAILURE);
	if (sle->state == STATE_INCSEARCH || sle->state == STATE_REVSEARCH)
	{
		vct_pop(sle->sub_line);
		set_redraw_flags(sle, RD_LINE | RD_CEND);
		return (SUCCESS);
	}
	if (sle->cursor.index == 0)
		return (FAILURE);
	index = sle->cursor.index <= 0 ? 0 : sle->cursor.index - 1;
	vct_del_char(sle->line, index);
	set_redraw_flags(sle, RD_LINE | RD_CMOVE);
	set_cursor_pos(sle, index);
	find_multiline_coord(sle, index);
	return (SUCCESS);
}

int8_t		ak_ctrl_d(__unused t_registry *shell, t_sle *sle)
{
	if (sle->state != STATE_STD && sle->state != STATE_REVSEARCH
					&& sle->state != STATE_INCSEARCH)
		return (FAILURE);
	if (sle->state == STATE_REVSEARCH || sle->state == STATE_INCSEARCH)
	{
		vct_reset(sle->line);
		set_redraw_flags(sle, RD_LINE | RD_CEND);
		sle->state = STATE_STD;
		return (SUCCESS);
	}
	if (sle->cursor.index == 0 && vct_len(sle->line) == 0)
	{
		vct_add(sle->line, 4);
		return (SUCCESS);
	}
	return (ak_delete(shell, sle));
}

int8_t		ak_ctrl_l(__unused t_registry *shell, t_sle *sle)
{
	if (sle->state != STATE_STD)
		return (FAILURE);
	set_redraw_flags(sle, RD_CLEAR | RD_CEND);
	return (SUCCESS);
}
