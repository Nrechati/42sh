/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_arrow_ak.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:21:29 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/02 19:56:49 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

static void				find_x3_coord(t_sle *sle, uint32_t prompt_len)
{
	char    *tmp;
	char    *tmp2;
	char    *line;
	int		sup;

	sle->cursor.x3 = 0;
	sle->cursor.y3 = 0;
	line = NULL;
	tmp = sle->line->buffer;
	while (tmp != NULL && *tmp != '\0' &&
			(tmp2 = ft_strchr(tmp + 1, '\n')) != NULL)
	{
		if (line == NULL)
			sup = (tmp2 - tmp + prompt_len) / sle->window.cols;
		else
			sup = (tmp2 - tmp) / sle->window.cols;
		while (sup-- > 0)
			sle->cursor.y3++;
		tmp = tmp2;
		line = tmp2;
		sle->cursor.y3++;
	}
	if (line == NULL)
	{
		while (sle->line->buffer[sle->cursor.x3] != '\0')
			sle->cursor.x3++;
		sle->cursor.x3 += prompt_len;
	}
	else
		while (line[1 + sle->cursor.x3] != '\0')
			sle->cursor.x3++;
}

static void				find_x2_coord(t_sle *sle, uint32_t prompt_len,
							int8_t offset)
{
	char		*tmp;
	char		*tmp2;
	char		*line;
	char		*cmd_offset;
	int			sup;

	sle->cursor.x2 = 0;
	sle->cursor.y2 = 0;
	cmd_offset = ft_strsub(sle->line->buffer, 0, sle->cursor.index + offset);
	tmp = cmd_offset;
	line = NULL;
	while (tmp != NULL && *tmp != '\0' &&
			(tmp2 = ft_strchr(tmp + 1, '\n')) != NULL)
	{
		if (line == NULL)
			sup = (tmp2 - tmp + prompt_len) / sle->window.cols;
		else
			sup = (tmp2 - tmp) / sle->window.cols;
		while (sup-- > 0)
			sle->cursor.y2++;
		tmp = tmp2;
		line = tmp2;
		sle->cursor.y2++;
	}
	if (line == NULL)
	{
		while (cmd_offset[sle->cursor.x2] != '\0')
			sle->cursor.x2++;
		sle->cursor.x2 += prompt_len;
	}
	else
		while (line[1 + sle->cursor.x2] != '\0')
			sle->cursor.x2++;
	ft_strdel(&cmd_offset);
}

void				find_multiline_coord(t_sle *sle, int8_t offset)
{
	uint32_t	prompt_len;

	prompt_len = get_prompt_length(&sle->prompt);
	find_x2_coord(sle, prompt_len, offset);
	find_x3_coord(sle, prompt_len);
}

int8_t				ak_arrow_right(t_registry *shell, t_sle *sle)
{
	int8_t offset;

	(void)shell;
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

int8_t				ak_arrow_left(t_registry *shell, t_sle *sle)
{
	int8_t offset;

	(void)shell;
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

int8_t				ak_arrow_up(t_registry *shell, t_sle *sle)
{
	uint64_t	len;
	char		*hist_cmd;

	(void)shell;
	if (sle->state != STATE_STD && sle->state != STATE_INCSEARCH
				&& sle->state != STATE_REVSEARCH)
		return (FAILURE);
	if (sle->state == STATE_STD && sle->line_save == NULL)
		sle->line_save = vct_dup(sle->line);
	if (sle->state == STATE_REVSEARCH || sle->state == STATE_INCSEARCH)
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

int8_t				ak_arrow_down(t_registry *shell, t_sle *sle)
{
	char 		*hist_cmd;
	uint64_t	len;

	(void)shell;
	if (sle->state != STATE_STD && sle->state != STATE_REVSEARCH
				&& sle->state != STATE_INCSEARCH)
		return (FAILURE);
	if (sle->state == STATE_REVSEARCH || sle->state == STATE_INCSEARCH)
		sle->state = STATE_STD;
	hist_cmd = history(NULL, NULL, GET_ENTRY | NEXT);
	if (hist_cmd == NULL && sle->line_save != NULL)
	{
		hist_cmd = vct_get_string(sle->line_save);
		history(NULL, NULL, RESET_HEAD);
	}
	if (hist_cmd == NULL)
	{
		history(NULL, NULL, RESET_HEAD);
		hist_cmd = "";
	}
	len = (vct_len(sle->line) == 0) ? 1 : vct_len(sle->line);
	vct_replace_string(sle->line, 0, len, hist_cmd);
	vct_del(&sle->line_save);
	sle->line_save = NULL;
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	find_multiline_coord(sle, 0);
	return (SUCCESS);
}
