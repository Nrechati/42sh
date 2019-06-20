/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_keys.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:13:31 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/20 10:49:58 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void		handle_printable_char(t_sle *sle, const char c)
{
	t_vector *line;
	t_cursor *cursor;

	if (sle->state != STATE_STD && sle->state != STATE_SEARCH)
		return ;
	cursor = &sle->cursor;
	line = sle->line;
	if (sle->state == STATE_SEARCH)
	{
		vct_add(sle->sub_line, c);
		set_redraw_flags(sle, RD_LINE | RD_CEND);
	}
	else if (cursor->index == 0)
	{
		vct_push(line, c);
		set_redraw_flags(sle, RD_LINE | RD_CMOVE);
		set_cursor_pos(sle, 1);
	}
	else if (cursor->index == vct_len(line))
	{
		vct_add(line, c);
		set_redraw_flags(sle, RD_LAST | RD_CEND);
	}
	else
	{
		vct_insert_char(line, c, cursor->index);
		set_redraw_flags(sle, RD_FPTP | RD_CMOVE);
		set_redraw_bounds(sle, cursor->index,
						vct_len(sle->line) + 1);
		set_cursor_pos(sle, cursor->index + 1);
	}
}

static void		handle_actionkey(t_registry *shell, t_sle *sle, char c[READ_SIZE])
{
	uint32_t	index;
	uint64_t	value;

	index = 0;
	value = compute_mask(c);
	while (index < AK_AMOUNT)
	{
		if (value == sle->ak_masks[index])
			sle->actionkeys[index](shell, sle);
		++index;
	}
}

void			handle_input_key(t_registry *shell, t_sle *sle, char c[READ_SIZE])
{
	if (is_printable(c) == TRUE)
		handle_printable_char(sle, c[0]);
	else
		handle_actionkey(shell, sle, c);
}
