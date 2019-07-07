/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_modes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 10:26:30 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/07 17:01:01 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

void			redrawmode_clear(t_registry *shell, t_sle *sle)
{
	tputs(sle->termcaps.clear, 1, &ft_putc);
	sle->cursor.x = 0;
	sle->cursor.y = 0;
	sle->cursor.index = 0;
	print_prompt(shell, sle);
}

void			redrawmode_last(t_sle *sle)
{
	t_coord		co;

	if (sle->rd_info.line_len >= sle->rd_info.disp_len)
	{
		index_to_coord(sle, sle->rd_info.prompt_len
						+ sle->rd_info.line_len - 1, &co);
		move_cursor_to_coord(sle, co.x, co.y);
		print_char(sle, vct_charat(sle->line,
						vct_len(sle->line) - 1));
	}
	else
	{
		index_to_coord(sle, sle->rd_info.prompt_len
						+ sle->rd_info.line_len - 1, &co);
		move_cursor_to_coord(sle, co.x, co.y);
		print_char(sle, ' ');
	}
}

void			redrawmode_line(t_sle *sle)
{
	t_coord		co;

	index_to_coord(sle, sle->rd_info.prompt_len, &co);
	move_cursor_to_coord(sle, co.x, co.y);
	tputs(sle->termcaps.clear_screen, 1, &ft_putc);
	tputs(sle->termcaps.clear_line, 1, &ft_putc);
	print_loop(sle, vct_get_string(sle->line));
}

void			redrawmode_fptp(t_sle *sle)
{
	char		c;
	t_coord		co;
	int64_t		length;
	int64_t		tmp;

	index_to_coord(sle, sle->window.point1 + sle->rd_info.prompt_len, &co);
	move_cursor_to_coord(sle, co.x, co.y);
	length = sle->window.point2 - (sle->window.point1 + 1);
	tmp = sle->window.point1;
	while (length > 0)
	{
		if ((c = vct_charat(sle->line, tmp)) != 0)
			print_char(sle, c);
		else
			print_char(sle, ' ');
		++tmp;
		--length;
	}
}
