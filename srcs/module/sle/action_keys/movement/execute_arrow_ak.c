/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_arrow_ak.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:21:29 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/08 13:34:31 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

int8_t				ak_arrow_right(t_sle *sle)
{
	int8_t offset;

	offset = 1;
	if (sle->cursor.index >= vct_len(sle->line))
		offset = 0;
	if (sle->visual_mode == TRUE)
	{
		sle->vis_stop = sle->cursor.index + offset;
//		add_redraw_flags(sle, RD_);
	}
	set_redraw_flags(sle, RD_NONE | RD_CMOVE);
	set_cursor_pos(sle, sle->cursor.index + offset);
	return (SUCCESS);
}

int8_t				ak_arrow_left(t_sle *sle)
{
	int8_t offset;

	offset = 1;
	if (sle->cursor.index == 0)
			offset = 0;
	if (sle->visual_mode == TRUE
			&& sle->cursor.index > 0)
		sle->vis_stop = sle->cursor.index - offset;
	set_cursor_pos(sle, sle->cursor.index - offset);
	set_redraw_flags(sle, RD_NONE | RD_CMOVE);
	return (SUCCESS);
}


int8_t				ak_arrow_up(t_sle *sle)
{
	char *hist_cmd;

	hist_cmd = history(NULL, NULL, GET_ENTRY | PREV);

	uint64_t len = (vct_len(sle->line) == 0) ? 1 : vct_len(sle->line);

	vct_replace_string(sle->line, 0, len ,hist_cmd);

	set_redraw_flags(sle, RD_LINE | RD_CEND);

	return (FAILURE);
}

int8_t				ak_arrow_down(__unused t_sle *sle)
{
	char *hist_cmd;

	hist_cmd = history(NULL, NULL, GET_ENTRY | NEXT);

	uint64_t len = (vct_len(sle->line) == 0) ? 1 : vct_len(sle->line);

	vct_replace_string(sle->line, 0, len ,hist_cmd);

	set_redraw_flags(sle, RD_LINE | RD_CEND);

	return (FAILURE);
}
