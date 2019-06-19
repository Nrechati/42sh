/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_modes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 10:26:30 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/19 11:34:12 by skuppers         ###   ########.fr       */
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

	if (sle->rd_info.line_len >= sle->rd_info.disp_len)
	{
		sle->rd_info.prompt_len += sle->rd_info.line_len - 1;
		index_to_coord(sle, sle->rd_info.prompt_len, &co);
		move_cursor_to_coord(sle, co.x, co.y);
		print_char(sle, vct_charat(sle->line,
						vct_len(sle->line) - 1));
	}
	else
	{
		sle->rd_info.prompt_len += sle->rd_info.line_len - 1;
		index_to_coord(sle, sle->rd_info.prompt_len, &co);
		move_cursor_to_coord(sle, co.x, co.y);
		print_char(sle, ' ');
	}
}

void	redrawmode_line(t_sle *sle)
{
	t_coord		co;
	int64_t		diff;
	char		*search;
	char 		*sl;

	//ft_printf("prompt_len: %d rev %d\n", sle->rd_info.prompt_len, ft_strlen(REV_SEARCH));

	index_to_coord(sle, sle->rd_info.prompt_len, &co);
	move_cursor_to_coord(sle, co.x, co.y);

	if (sle->state == STATE_SEARCH)
	{
		sl = vct_get_string(sle->sub_line);

		search = history(NULL, sl, GET_ENTRY | BY_NAME | sle->search_type);

		if (search == NULL)
			sle->search_line = vct_dups("Failed");
		else
			sle->search_line = vct_dups(search);

		search = NULL;
		ft_asprintf(&search, "%s`%s`:%s",
					(sle->search_type == NEXT) ? INC_SEARCH : REV_SEARCH,
					vct_get_string(sle->sub_line),
					vct_get_string(sle->search_line));

		sle->line = vct_dups(search);
	}

	diff = vct_len(sle->line) - (vct_len(sle->window.displayed_line)) - 1;
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

	index_to_coord(sle, sle->window.point1 + sle->rd_info.prompt_len, &co);
	move_cursor_to_coord(sle, co.x, co.y);

	length = sle->window.point2 - (sle->window.point1 + 1);

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
	sle->window.point2 = (sle->rd_info.line_len
					> sle->rd_info.disp_len)
					? sle->rd_info.line_len
					: sle->rd_info.disp_len;
	++sle->window.point2;
	redrawmode_fptp(sle);
}

void	redrawmode_fstp(t_sle *sle)
{
	sle->window.point1 = 0;
	redrawmode_fptp(sle);
}
