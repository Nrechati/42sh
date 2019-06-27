/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_arrow_ak.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:21:29 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/27 14:32:17 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

static uint8_t	find_multiline_coord(char *cmd, t_coord *coord, uint32_t offset,
									uint32_t len_prompt)
{
	char	*tmp;
	char	*cmd_offset;
	char	*line;
	int		nb_nl;

	nb_nl = 0;
	coord->x = 0;
	coord->y = 0;
	cmd_offset = ft_strsub(cmd, 0, offset);
	tmp = cmd_offset;
	line = NULL;
	while ((tmp = ft_strchr(tmp + 1, '\n')) != NULL)
	{
		line = tmp;
		nb_nl++;
	}
	if (line == NULL)
	{
		while (cmd_offset[coord->x] != '\0')
			coord->x++;
		coord->x += len_prompt;
	}
	else
	{
		coord->y = nb_nl;
			line++;
		while (line[coord->x] != '\0')
			coord->x++;
	}
	ft_dprintf(3, "COOORD last_line_len: %d, drawed_lines %d\n", coord->x, coord->y);
	ft_strdel(&cmd_offset);
	return (TRUE);
}

int8_t				ak_arrow_right(__unused t_registry *shell, t_sle *sle)
{
	int8_t offset;
	t_coord	coord;

	if (sle->state != STATE_STD && sle->state != STATE_VISUAL)
		return (FAILURE);
	offset = 1;
//	if (sle->cursor.index >= vct_len(sle->line))
//		offset = 0;
	if (sle->state == STATE_VISUAL)
		sle->vis_stop = sle->cursor.index + offset;
	set_redraw_flags(sle, RD_NONE | RD_CMOVE);
	if (find_multiline_coord(sle->line->buffer, &coord, sle->cursor.index,
				get_prompt_length(&sle->prompt)) == TRUE)
	{
		sle->cursor.x2 = coord.x;
		sle->cursor.y2 = coord.y;
	}
	set_cursor_pos(sle, sle->cursor.index + offset);
	return (SUCCESS);
}

int8_t				ak_arrow_left(__unused t_registry *shell, t_sle *sle)
{
	int8_t offset;
	t_coord	coord;

	if (sle->state != STATE_STD && sle->state != STATE_VISUAL)
		return (FAILURE);
	offset = 1;
//	if (sle->cursor.index == 0)
//			offset = 0;
	if (sle->state == STATE_VISUAL && sle->cursor.index > 0)
		sle->vis_stop = sle->cursor.index - offset;
	set_cursor_pos(sle, sle->cursor.index - offset);
	if (find_multiline_coord(sle->line->buffer, &coord, sle->cursor.index,
				get_prompt_length(&sle->prompt)) == TRUE)
	{
		sle->cursor.x2 = coord.x;
		sle->cursor.y2 = coord.y;
	}
	set_redraw_flags(sle, RD_NONE | RD_CMOVE);
	return (SUCCESS);
}

int8_t				ak_arrow_up(__unused t_registry *shell, t_sle *sle)
{
	char		*hist_cmd;
	t_coord		coord;	
	uint64_t	len;

	if (sle->state != STATE_STD && sle->state != STATE_SEARCH)
		return (FAILURE);
	if (sle->state == STATE_STD && sle->line_save == NULL)
		sle->line_save = vct_dup(sle->line);
	if (sle->state == STATE_SEARCH)
		sle->state = STATE_STD;
	//sle->window.last_line_len = 0;
	hist_cmd = history(NULL, NULL, GET_ENTRY | PREV);
	if (hist_cmd == NULL)
		return (FAILURE);
	len = (vct_len(sle->line) == 0) ? 1 : vct_len(sle->line);
	vct_replace_string(sle->line, 0, len, hist_cmd);
	if (find_multiline_coord(sle->line->buffer, &coord, sle->cursor.index,
				get_prompt_length(&sle->prompt)) == TRUE)
	{
		sle->cursor.x2 = coord.x;
		sle->cursor.y2 = coord.y;
	}
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	return (FAILURE);
}

int8_t				ak_arrow_down(__unused t_registry *shell, __unused t_sle *sle)
{
	char 		*hist_cmd;
	uint64_t	len;
	t_coord		coord;	

	if (sle->state != STATE_STD && sle->state != STATE_SEARCH)
		return (FAILURE);
	if (sle->state == STATE_SEARCH)
		sle->state = STATE_STD;
	sle->window.last_line_len = 0;
	hist_cmd = history(NULL, NULL, GET_ENTRY | NEXT);
	if (hist_cmd == NULL && sle->line_save != NULL)
	{
		hist_cmd = vct_get_string(sle->line_save);
		sle->line_save = NULL;
		history(NULL, NULL, RESET_HEAD);
	}
	len = (vct_len(sle->line) == 0) ? 1 : vct_len(sle->line);
	if (hist_cmd != NULL)
	{
		vct_replace_string(sle->line, 0, len, hist_cmd);
		if (find_multiline_coord(sle->line->buffer, &coord, sle->cursor.index,
					get_prompt_length(&sle->prompt)) == TRUE)
		{
			sle->cursor.x2 = coord.x;
			sle->cursor.y2 = coord.y;
		}
		set_redraw_flags(sle, RD_LINE | RD_CEND);
	}
	return (FAILURE);
}
