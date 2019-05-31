/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 09:34:43 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/31 11:45:30 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>
#include "interface_functions.h"

#include "log.h"

void     move_cursor_to_coord(t_interface *itf, uint64_t x, uint64_t y)
{
    int64_t x_moves;
    int64_t y_moves;

	ft_dprintf(3, "\n\n\n");
	log_print(g_shell, LOG_INFO, "GOTO coord x:%lu y:%lu.\n", x, y);

	y_moves =  (y - itf->cursor.y);
	ft_dprintf(3, "Ymoves is %lu - %lu\n", y, itf->cursor.y);
	log_print(g_shell, LOG_INFO, "NEED to move y:%ld times.\n", y_moves);
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
		itf->cursor.y--;
	}

    x_moves =  (x - itf->cursor.x);
//	log_print(g_shell, LOG_INFO, "NEED to move x:%ld times.\n", x_moves);
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
//	itf->cursor.y = y;
	ft_dprintf(3, "Cursor is now at X:%lu Y:%lu\n", x, y);
}

void     move_cursor(t_registry *shell)
{
	t_coord		*coord;
    uint64_t    rd_flag;

	coord = NULL;
    rd_flag = shell->interface.window.rd_flag;


    if (rd_flag & RD_CEND)
    {
		coord = index_to_coord(&shell->interface.window,
								get_prompt_length(&shell->interface.prompt)
								+ vct_len(shell->interface.line));
		move_cursor_to_coord(&shell->interface, coord->x, coord->y);

		shell->interface.cursor.index = vct_len(shell->interface.line);
    }
    else if (rd_flag & RD_CHOME)
    {
		coord = index_to_coord(&shell->interface.window,
								get_prompt_length(&shell->interface.prompt));
		move_cursor_to_coord(&shell->interface, coord->x, coord->y);
		shell->interface.cursor.index = 0;
    }
    else if (rd_flag & RD_CMOVE)
    {
		if (shell->interface.window.point_cursor
						> vct_len(shell->interface.line))
			return ;
		coord = index_to_coord(&shell->interface.window,
								get_prompt_length(&shell->interface.prompt)
								+ shell->interface.window.point_cursor);
		move_cursor_to_coord(&shell->interface, coord->x, coord->y);
		shell->interface.cursor.index = shell->interface.window.point_cursor;
    }
	free(coord);
}
