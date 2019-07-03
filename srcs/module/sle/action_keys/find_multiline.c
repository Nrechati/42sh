/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_multiline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:00:20 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/03 15:01:42 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

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

void					find_multiline_coord(t_sle *sle, int8_t offset)
{
	uint32_t	prompt_len;

	prompt_len = get_prompt_length(&sle->prompt);
	find_x2_coord(sle, prompt_len, offset);
	find_x3_coord(sle, prompt_len);
}
