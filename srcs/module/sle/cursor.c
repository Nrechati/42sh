/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 09:34:43 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/04 17:13:17 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

static inline void move_x(t_interface *itf, uint64_t x)
{
    int64_t x_moves;

	x_moves =  (x - itf->cursor.x);
	while (x_moves < 0)
	{
		++x_moves;
        tputs(itf->termcaps.left, 1, &ft_putc);
		itf->cursor.index--;
	}
    while (x_moves > 0)
	{
		--x_moves;
   		tputs(itf->termcaps.right, 1, &ft_putc);
		itf->cursor.index++;
	}
	itf->cursor.x = x;
}

static inline void move_y(t_interface *itf, uint64_t y)
{
	int64_t y_moves;

	y_moves =  (y - itf->cursor.y);
	while (y_moves > 0)
	{
		--y_moves;
   	    tputs(itf->termcaps.down, 1, &ft_putc);
		itf->cursor.index += itf->window.cols;
		if (y_moves == 0)
			itf->cursor.x = 0;
	}
    while (y_moves < 0)
	{
		++y_moves;
		tputs(itf->termcaps.up, 1, &ft_putc);
		itf->cursor.index -= itf->window.cols;
	}
	itf->cursor.y = y;
}

void     move_cursor_to_coord(t_interface *itf, uint64_t x, uint64_t y)
{
	move_y(itf, y);
	move_x(itf, x);
}

static inline void cursor_move(t_interface *itf)
{
	t_coord		*coord;

	if (itf->window.point_cursor
					> vct_len(itf->line))
		return ;
	coord = index_to_coord(itf,
						get_prompt_length(&itf->prompt)
						+ itf->window.point_cursor);
	move_cursor_to_coord(itf, coord->x, coord->y);
	itf->cursor.index = itf->window.point_cursor;
	free(coord);
}

void     move_cursor(t_registry *shell)
{
	t_coord		*coord;
    uint64_t    rd_flag;

	coord = NULL;
    rd_flag = shell->interface.window.rd_flag;
    if (rd_flag & RD_CEND)
    {
		coord = index_to_coord(&shell->interface,
								get_prompt_length(&shell->interface.prompt)
								+ vct_len(shell->interface.line));
		move_cursor_to_coord(&shell->interface, coord->x, coord->y);
		shell->interface.cursor.index = vct_len(shell->interface.line);
    }
    else if (rd_flag & RD_CHOME)
    {
		coord = index_to_coord(&shell->interface,
								get_prompt_length(&shell->interface.prompt));
		move_cursor_to_coord(&shell->interface, coord->x, coord->y);
		shell->interface.cursor.index = 0;
    }
    else if (rd_flag & RD_CMOVE)
    	cursor_move(&shell->interface);
	if (coord != NULL)
		free(coord);
}
