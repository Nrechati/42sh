/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_multiline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:00:20 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/04 15:19:48 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void		find_x3_coord(t_sle *sle, char *line, uint32_t prompt_len)
{
	if (line == NULL)
	{
		if (sle->line != NULL && sle->line->buffer != NULL)
			sle->cursor.x3 = vct_len(sle->line);
		sle->cursor.x3 += prompt_len;
	}
	else
		sle->cursor.x3 = ft_strlen(line);
	if (sle->cursor.x3 > sle->window.cols)
	{
		sle->cursor.y3 += sle->cursor.x3 / sle->window.cols;
		sle->cursor.x3 = sle->cursor.x3 % sle->window.cols;
	}
}

static void		find_y3_coord(t_sle *sle, uint32_t prompt_len)
{
	char	*tmp;
	char	*tmp2;
	char	*line;
	int		sup;

	sle->cursor.x3 = 0;
	sle->cursor.y3 = 0;
	line = NULL;
	tmp = sle->line->buffer;
	while (tmp != NULL && *tmp != '\0' &&
			(tmp2 = ft_strchr(tmp, '\n')) != NULL)
	{
		sup = (tmp2 - tmp + (line == NULL ? prompt_len : 0)) / sle->window.cols;
		while (sup-- > 0)
			sle->cursor.y3++;
		tmp2++;
		tmp = tmp2;
		line = tmp2;
		sle->cursor.y3++;
	}
	find_x3_coord(sle, line, prompt_len);
}

static void		find_x2_coord(t_sle *sle, char *line, uint32_t prompt_len,
					char *cmd_offset)
{
	if (line == NULL)
	{
		if (cmd_offset != NULL)
			sle->cursor.x2 = ft_strlen(cmd_offset);
		sle->cursor.x2 += prompt_len;
	}
	else
		sle->cursor.x2 = ft_strlen(line);
	if (sle->cursor.x2 > sle->window.cols)
	{
		sle->cursor.y2 += sle->cursor.x2 / sle->window.cols;
		sle->cursor.x2 = sle->cursor.x2 % sle->window.cols;
	}
	ft_strdel(&cmd_offset);
}

static void		find_y2_coord(t_sle *sle, uint32_t prompt_len, int8_t offset)
{
	char		*tmp;
	char		*tmp2;
	char		*line;
	char		*cmd_offset;
	int			sup;

	sle->cursor.x2 = 0;
	sle->cursor.y2 = 0;
	cmd_offset = ft_strsub(sle->line->buffer, 0,
					(((int32_t)sle->cursor.index + offset) <= 0)
					? 1 : sle->cursor.index + offset);
	tmp = cmd_offset;
	line = NULL;
	while (tmp != NULL && *tmp != '\0' &&
			(tmp2 = ft_strchr(tmp, '\n')) != NULL)
	{
		sup = (tmp2 - tmp + (line == NULL ? prompt_len : 0)) / sle->window.cols;
		while (sup-- > 0)
			sle->cursor.y2++;
		tmp2++;
		tmp = tmp2;
		line = tmp2;
		sle->cursor.y2++;
	}
	find_x2_coord(sle, line, prompt_len, cmd_offset);
}

void			find_multiline_coord(t_sle *sle, int8_t offset)
{
	uint32_t	prompt_len;

	prompt_len = get_prompt_length(&sle->prompt);
	find_y2_coord(sle, prompt_len, offset);
	find_y3_coord(sle, prompt_len);
	ft_dprintf(3, "y3: %d, x3: %d\n", sle->cursor.y3, sle->cursor.x3);
	ft_dprintf(3, "y2: %d, x2: %d\n", sle->cursor.y2, sle->cursor.x2);
}
