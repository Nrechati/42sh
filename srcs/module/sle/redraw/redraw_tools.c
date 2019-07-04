/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 09:48:40 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/03 15:50:48 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

void			index_to_coord(t_sle *sle, uint64_t index, t_coord *co)
{
	if (sle->window.cols == 0)
		return ;
	if (index > sle->rd_info.line_len + sle->rd_info.prompt_len + 1)
		index = sle->rd_info.line_len + sle->rd_info.prompt_len;
	if (sle->window.cols != 0)
	{
		co->x = (index % sle->window.cols);
		co->y = (index / sle->window.cols);
	}
}

void			print_char(t_sle *sle, char c)
{
	write(1, &c, 1);
	sle->cursor.x++;
	sle->cursor.index++;
	if (sle->cursor.x == sle->window.cols || c == '\n')
	{
		if (c != '\n')
			tputs(sle->termcaps.down, 2, &ft_putc);
		sle->cursor.y++;
		sle->cursor.x = 0;
	}
}

void			print_loop(t_sle *sle, char *str)
{
	size_t		i;
	int			active;

	i = 0;
	active = FALSE;
	tputs(sle->termcaps.normal_cursor, 1, &ft_putc);
	if (sle->state == STATE_REVSEARCH || sle->state == STATE_INCSEARCH
		|| (sle->state == STATE_VISUAL
		&& sle->window.point1 - sle->window.point2 != 0))
		tputs(sle->termcaps.hidden_cursor, 1, &ft_putc);
	while (str[i] != '\0')
	{
		if (sle->state == STATE_VISUAL && i >= sle->window.point1
				&& i < sle->window.point2)
		{
			tputs(sle->termcaps.standout_on, 1, &ft_putc);
			active = TRUE;
		}
		else if (active == TRUE)
		{
			tputs(sle->termcaps.standout_off, 1, &ft_putc);
			active = FALSE;
		}
		print_char(sle, str[i++]);
	}
	tputs(sle->termcaps.standout_off, 1, &ft_putc);
}

uint32_t		write_esc_sequence(char *str, uint32_t index)
{
	char		*esc;
	uint32_t	length;

	esc = NULL;
	length = 2;
	if (str[index + length] != '[')
		return (length - 1);
	while (str[++length + index] != '\0')
	{
		if (str[length + index] != ';'
				&& str[length + index] != 'm'
				&& !ft_isdigit(str[length + index]))
			return (length);
		if (str[index + length] == 'm')
		{
			esc = ft_strsub(str, index + 1, length);
			esc[0] = 27;
			ft_printf("%s", esc);
			ft_strdel(&esc);
			break ;
		}
	}
	return (length + 1);
}

void			print_prompt_to_window(t_sle *sle, t_vector *text)
{
	uint32_t	index;
	char		*str;

	index = 0;
	str = vct_get_string(text);
	while (str[index] != '\0')
	{
		if (str[index] == '\\' && str[index + 1] == 'e')
			index += write_esc_sequence(str, index);
		write(1, &str[index], 1);
		++index;
		if (sle->cursor.x == sle->window.cols)
		{
			sle->cursor.y++;
			sle->cursor.x = 0;
		}
		sle->cursor.x++;
	}
	sle->prompt.length = (sle->cursor.y * sle->window.cols) + sle->cursor.x;
}
