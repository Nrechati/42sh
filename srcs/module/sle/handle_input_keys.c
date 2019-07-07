/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_keys.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:13:31 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/07 17:03:45 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void			handle_insertion(t_sle *sle, char c)
{
	t_cursor	*cursor;
	t_vector	*line;

	line = sle->line;
	cursor = &sle->cursor;
	vct_insert_char(line, c, cursor->index);
	set_redraw_flags(sle, RD_LINE | RD_CMOVE);
	set_redraw_bounds(sle, cursor->index,
					vct_len(sle->line) + 1);
	set_cursor_pos(sle, cursor->index + 1);
	find_multiline_coord(sle, 1);
}

static void			handle_printable_char(t_sle *sle, const char c)
{
	t_vector *line;
	t_cursor *cursor;

	if (sle->state != STATE_STD)
		return ;
	cursor = &sle->cursor;
	line = sle->line;
	if (cursor->index == 0)
	{
		vct_push(line, c);
		set_redraw_flags(sle, RD_LINE | RD_CMOVE);
		set_cursor_pos(sle, 1);
		find_multiline_coord(sle, 1);
	}
	else if (cursor->index == vct_len(line))
	{
		vct_add(line, c);
		set_redraw_flags(sle, RD_LINE | RD_CEND);
		find_multiline_coord(sle, 1);
	}
	else
		handle_insertion(sle, c);
}

static void			handle_actionkey(t_registry *shell,
				t_sle *sle, char c[READ_SIZE])
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

void				handle_input_key(t_registry *shell,
				t_sle *sle, char c[READ_SIZE])
{
	if (is_printable(c) == TRUE)
	{
		handle_printable_char(sle, c[0]);
		history(NULL, NULL, RESET_HEAD);
		vct_del(&sle->line_save);
	}
	else
		handle_actionkey(shell, sle, c);
}
