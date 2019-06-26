/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_special_ak.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:20:05 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/21 16:00:01 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t		ak_ctrl_t(__unused t_registry *shell, __unused t_sle *sle)
{
	sle->state = STATE_SEARCH;
	sle->search_type = NEXT;
	ft_bzero(sle->line->buffer, sle->line->size);
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	return (SUCCESS);
}

int8_t		ak_ctrl_r(__unused t_registry *shell, t_sle *sle)
{
	sle->state = STATE_SEARCH;
	sle->search_type = PREV;
	ft_bzero(sle->line->buffer, sle->line->size);
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	return (SUCCESS);
}

int8_t		ak_hightab(t_registry *shell, t_sle *sle)
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
		ft_strdel(&substring);
		vct_insert_string(sle->line, ret_completion, sle->cursor.index);
	}
	else
	{
		ft_strdel(&substring);
		ft_putendl("");
		print_prompt(shell, sle);
	}
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	return (SUCCESS);
}

int8_t		ak_delete(__unused t_registry *shell, t_sle *sle)
{
	if (sle->state != STATE_STD)
		return (FAILURE);
	vct_del_char(sle->line, sle->cursor.index);
	set_redraw_flags(sle, RD_FPTE | RD_CMOVE);
	set_redraw_bounds(sle, sle->cursor.index - 1, 0);
	set_cursor_pos(sle, sle->cursor.index);
	return (SUCCESS);
}

int8_t		ak_backspace(__unused t_registry *shell, t_sle *sle)
{
	if (sle->state != STATE_STD && sle->state != STATE_SEARCH)
		return (FAILURE);
	if (sle->state == STATE_SEARCH)
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
	if (sle->state != STATE_STD)
		return (FAILURE);
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
