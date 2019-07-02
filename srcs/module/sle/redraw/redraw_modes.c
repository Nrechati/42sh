/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_modes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 10:26:30 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/02 19:52:38 by skuppers         ###   ########.fr       */
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
		index_to_coord(sle, sle->rd_info.prompt_len + sle->rd_info.line_len - 1, &co);
		move_cursor_to_coord(sle, co.x, co.y);
		print_char(sle, vct_charat(sle->line,
						vct_len(sle->line) - 1));
	}
	else
	{
		index_to_coord(sle, sle->rd_info.prompt_len+sle->rd_info.line_len - 1,
						&co);
		move_cursor_to_coord(sle, co.x, co.y);
		print_char(sle, ' ');
	}
}

static void	state_search(t_sle *sle)
{
	char		*search;
	char 		*sl;

	search = NULL;
	tputs(sle->termcaps.hidden_cursor, 1, &ft_putc);
	sl = vct_get_string(sle->sub_line);
	search = history(NULL, sl, GET_ENTRY | BY_NAME | sle->search_type);
	vct_del(&sle->search_line);
	vct_del(&sle->line);
	if (search == NULL && sl != NULL && *sl != '\0')
		sle->search_line = vct_dups("Failed");
	else if (search != NULL)
		sle->search_line = vct_dups(search);
	else
		sle->search_line = vct_dups("");
	search = NULL;
	ft_asprintf(&search, "%s`%s`:%s",
				(sle->search_type == NEXT) ? INC_SEARCH : REV_SEARCH,
				vct_get_string(sle->sub_line),
				vct_get_string(sle->search_line));
	sle->line = vct_dups(search);
	ft_strdel(&search);
}

void	redrawmode_line(t_sle *sle)
{
	t_coord		co;

	index_to_coord(sle, sle->rd_info.prompt_len, &co);
	move_cursor_to_coord(sle, co.x, co.y);
	if (sle->state == STATE_REVSEARCH || sle->state == STATE_INCSEARCH)
		state_search(sle);
	else
		tputs(sle->termcaps.normal_cursor, 1, &ft_putc);
	tputs(sle->termcaps.clear_screen, 1 , &ft_putc);
	print_loop(sle, vct_get_string(sle->line));
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
