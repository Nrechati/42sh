/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 09:41:12 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/19 18:17:55 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <sys/ioctl.h>

uint64_t	update_winsize(t_sle *sle)
{
	struct winsize w;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == FAILURE)
        return (CRITICAL_ERROR | WINDOW_FAIL);
	sle->window.rows = (w.ws_row <= 0) ? 1 : w.ws_row;
	sle->window.cols = (w.ws_col <= 0) ? 1 : w.ws_col;
    sle->window.max_chars = sle->window.rows * sle->window.cols;
	return (SUCCESS);
}

void	update_window(t_sle *sle)
{
	update_winsize(sle);
	sle->cursor.x = 0;
	sle->cursor.y = 0;
	sle->cursor.index = 0;
}

void	redraw_window(__unused  t_sle *sle)
{
//	update_winsize(sle);
//	update_window(sle);
//	ft_printf("Updating window. r%lu c%lu\n", sle->window.rows, sle->window.cols);
//	set_redraw_flags(sle, RD_LINE | RD_CEND);
//	redraw(NULL, sle);
}
