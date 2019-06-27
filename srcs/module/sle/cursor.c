/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 09:34:43 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/27 11:11:28 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

static inline void move_x(t_sle *sle, uint64_t x)
{
    int64_t x_moves;

	x_moves =  (x - sle->cursor.x);
	while (x_moves < 0)
	{
		++x_moves;
        tputs(sle->termcaps.left, 1, &ft_putc);
		sle->cursor.index--;
	}
    while (x_moves > 0)
	{
		--x_moves;
   		tputs(sle->termcaps.right, 1, &ft_putc);
		sle->cursor.index++;
	}
	sle->cursor.x = x;
}

static inline void move_y(t_sle *sle, uint64_t y)
{
	int64_t y_moves;

	y_moves =  (y - sle->cursor.y);
	while (y_moves > 0)
	{
		--y_moves;
   	    tputs(sle->termcaps.down, 1, &ft_putc);
		sle->cursor.index += sle->window.cols;
		if (y_moves == 0)
			sle->cursor.x = 0;
	}
    while (y_moves < 0)
	{
		++y_moves;
		tputs(sle->termcaps.up, 1, &ft_putc);
		sle->cursor.index -= sle->window.cols;
	}
	sle->cursor.y = y;
}

void     move_cursor_to_coord(t_sle *sle, uint64_t x, uint64_t y)
{
	move_y(sle, y);
	move_x(sle, x);
}

static inline void cursor_move(t_sle *sle)
{
	t_coord		coord;

	if (sle->window.point_cursor > vct_len(sle->line))
		return ;
	index_to_coord(sle, get_prompt_length(&sle->prompt)
						+ sle->window.point_cursor, &coord,
						sle->window.drawed_lines);
	move_cursor_to_coord(sle, coord.x, coord.y);
	sle->cursor.index = sle->window.point_cursor;
}

void     move_cursor(t_sle *sle)
{
	t_coord		coord;
    uint64_t    rd_flag;
	uint64_t	offset;

	offset = 0;
    rd_flag = sle->window.rd_flag;
    if (rd_flag & RD_CEND)
    {
		offset = 0;//(sle->window.drawed_lines * sle->window.cols);
		index_to_coord(sle, get_prompt_length(&sle->prompt)
						+ vct_len(sle->line)
						+ offset, &coord,
						sle->window.drawed_lines);
		move_cursor_to_coord(sle, coord.x, coord.y);
		sle->cursor.index = vct_len(sle->line);
    }
    else if (rd_flag & RD_CHOME)
    {
		index_to_coord(sle, get_prompt_length(&sle->prompt) , &coord,
						sle->window.drawed_lines);
		move_cursor_to_coord(sle, coord.x, coord.y);
		sle->cursor.index = 0;
    }
    else if (rd_flag & RD_CMOVE)
    	cursor_move(sle);
}
