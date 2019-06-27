/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_arrow_ak.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:21:29 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/27 19:58:39 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

static void            find_x3_coord(t_sle *sle)
{
	char    *tmp2;
	char    *line2;

	sle->cursor.x3 = 0;
	sle->cursor.y3 = 0;
	line2 = NULL;
	tmp2 = sle->line->buffer;
	while ((tmp2 = ft_strchr(tmp2 + 1, '\n')) != NULL)
	{
		line2 = tmp2;
		sle->cursor.y3++;
	}
	if (line2 == NULL)
	{
		while (sle->line->buffer[sle->cursor.x3] != '\0')
			sle->cursor.x3++;
		sle->cursor.x3 += get_prompt_length(&sle->prompt);
	}
	else
		while (line2[1 + sle->cursor.x3] != '\0')
			sle->cursor.x3++;
}

static void            find_x2_coord(t_sle *sle, int8_t offset)
{
	char    *tmp;
	char    *line;
	char    *cmd_offset;

	sle->cursor.x2 = 0;
	sle->cursor.y2 = 0;
	cmd_offset = ft_strsub(sle->line->buffer, 0, sle->cursor.index + offset);
	tmp = cmd_offset;
	line = NULL;
	while ((tmp = ft_strchr(tmp + 1, '\n')) != NULL)
	{
		line = tmp;
		sle->cursor.y2++;
	}
	if (line == NULL)
	{
		while (cmd_offset[sle->cursor.x2] != '\0')
			sle->cursor.x2++;
		sle->cursor.x2 += get_prompt_length(&sle->prompt);
	}
	else
		while (line[1 + sle->cursor.x2] != '\0')
			sle->cursor.x2++;
	ft_strdel(&cmd_offset);
}

void            find_multiline_coord(t_sle *sle, int8_t offset)
{
	find_x2_coord(sle, offset);
	find_x3_coord(sle);
}


int8_t				ak_arrow_right(__unused t_registry *shell, t_sle *sle)
{
	int8_t offset;

	if (sle->state != STATE_STD && sle->state != STATE_VISUAL)
		return (FAILURE);
	offset = 1;
	if (sle->cursor.index >= vct_len(sle->line))
		offset = 0;
	if (sle->state == STATE_VISUAL)
		sle->vis_stop = sle->cursor.index + offset;
	set_cursor_pos(sle, sle->cursor.index + offset);
	set_redraw_flags(sle, RD_NONE | RD_CMOVE);
	find_multiline_coord(sle, offset);
	return (SUCCESS);
}

int8_t				ak_arrow_left(__unused t_registry *shell, t_sle *sle)
{
	int8_t offset;

	if (sle->state != STATE_STD && sle->state != STATE_VISUAL)
		return (FAILURE);
	offset = -1;
	if (sle->cursor.index == 0)
		offset = 0;
	if (sle->state == STATE_VISUAL && sle->cursor.index > 0)
		sle->vis_stop = sle->cursor.index + offset;
	set_cursor_pos(sle, sle->cursor.index + offset);
	set_redraw_flags(sle, RD_NONE | RD_CMOVE);
	find_multiline_coord(sle, offset);
	return (SUCCESS);
}

int8_t				ak_arrow_up(__unused t_registry *shell, t_sle *sle)
{
	char		*hist_cmd;
	uint64_t	len;

	if (sle->state != STATE_STD && sle->state != STATE_SEARCH)
		return (FAILURE);
	if (sle->state == STATE_STD && sle->line_save == NULL)
		sle->line_save = vct_dup(sle->line);
	if (sle->state == STATE_SEARCH)
		sle->state = STATE_STD;
	hist_cmd = history(NULL, NULL, GET_ENTRY | PREV);
	if (hist_cmd == NULL)
		return (FAILURE);
	len = (vct_len(sle->line) == 0) ? 1 : vct_len(sle->line);
	vct_replace_string(sle->line, 0, len, hist_cmd);
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	find_multiline_coord(sle, 0);
	return (SUCCESS);
}

int8_t				ak_arrow_down(__unused t_registry *shell,
		__unused t_sle *sle)
{
	char 		*hist_cmd;
	uint64_t	len;

	if (sle->state != STATE_STD && sle->state != STATE_SEARCH)
		return (FAILURE);
	if (sle->state == STATE_SEARCH)
		sle->state = STATE_STD;
	hist_cmd = history(NULL, NULL, GET_ENTRY | NEXT);
	if (hist_cmd == NULL && sle->line_save != NULL)
	{
		hist_cmd = vct_get_string(sle->line_save);
		sle->line_save = NULL;
		history(NULL, NULL, RESET_HEAD);
	}
	if (hist_cmd == NULL)
		return (FAILURE);
	len = (vct_len(sle->line) == 0) ? 1 : vct_len(sle->line);
	vct_replace_string(sle->line, 0, len, hist_cmd);
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	find_multiline_coord(sle, 0);
	return (SUCCESS);
}
