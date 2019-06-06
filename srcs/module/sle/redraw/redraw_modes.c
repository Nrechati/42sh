/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_modes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 10:26:30 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/06 16:01:12 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

void	redrawmode_clear(t_registry *shell, t_sle *sle)
{
	tputs(sle->termcaps.clear, 1, &ft_putc);
	sle->cursor.x = 0;
	sle->cursor.y = 0;
	sle->cursor.index = 0;
	print_prompt(shell, sle);
}

void	redrawmode_last(t_sle *sle)
{
	t_coord		co;
	uint64_t	prompt_len;
	uint64_t 	line_len;
	uint64_t 	disp_len;

	line_len  = vct_len(sle->line);
	disp_len  = vct_len(sle->window.displayed_line);
	prompt_len = get_prompt_length(&sle->prompt);
	if (line_len >= disp_len)
	{
		prompt_len += line_len - 1;
		index_to_coord(sle, prompt_len, &co);
		move_cursor_to_coord(sle, co.x, co.y);
		print_char(sle, vct_charat(sle->line,
						vct_len(sle->line) - 1));
	}
	else
	{
		prompt_len += line_len - 1;
		index_to_coord(sle, prompt_len, &co);
		move_cursor_to_coord(sle, co.x, co.y);
		print_char(sle, ' ');
	}
}

void	redrawmode_line(t_sle *sle)
{
	t_coord		co;
	int64_t		diff;
	uint64_t	prompt_len;

	prompt_len = get_prompt_length(&sle->prompt);
	index_to_coord(sle, prompt_len, &co);
	move_cursor_to_coord(sle, co.x, co.y);

	diff = vct_len(sle->line)
			- (vct_len(sle->window.displayed_line));
	print_loop(sle, vct_get_string(sle->line));
	if (diff <= 0)
	{
		while (++diff <= 0)
			print_char(sle, ' ');
	}
}

void	redrawmode_fptp(t_sle *sle)
{
	char 		c;
	t_coord		co;
	int64_t		length;
	int64_t		tmp;

	index_to_coord(sle, sle->window.point1
						+ get_prompt_length(&sle->prompt), &co);
	move_cursor_to_coord(sle, co.x, co.y);

	length = sle->window.point2
			- (sle->window.point1 + 1);

	tmp = sle->window.point1;
	while (length  > 0)
	{
		if ((c = vct_charat(sle->line, tmp)) != 0)
			print_char(sle, c);
		else
			print_char(sle, ' ');
		++tmp;
		--length;
	}
}

void	redrawmode_fpte(t_sle *sle)
{
	uint64_t	line_len;
	uint64_t	disp_len;

	line_len = vct_len(sle->line);
	disp_len = vct_len(sle->window.displayed_line);
	sle->window.point2 = (line_len > disp_len) ? line_len : disp_len;
	++sle->window.point2;
	redrawmode_fptp(sle);
}

void	redrawmode_fstp(t_sle *sle)
{
	sle->window.point1 = 0;
	redrawmode_fptp(sle);
}
