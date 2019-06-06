/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 09:41:12 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/04 17:14:04 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <sys/ioctl.h>

uint64_t	update_winsize(t_registry *shell, t_sle *sle)
{
	struct winsize w;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == FAILURE)
        return (CRITICAL_ERROR | WINDOW_FAIL);
	sle->window.rows = (w.ws_row <= 0) ? 0 : w.ws_row;
	sle->window.cols = (w.ws_col <= 0) ? 0 : w.ws_col;
    sle->window.max_chars = sle->window.rows * sle->window.cols;
    if (add_nbr_var(&shell->intern, INT_COLS, sle->window.cols, SET_VAR) == FAILURE)
		return (WINDOW_FAIL | INTERNAL_FAIL);
	if (add_nbr_var(&shell->intern, INT_ROWS, sle->window.rows, SET_VAR) == FAILURE)
		return (WINDOW_FAIL | INTERNAL_FAIL);
	return (SUCCESS);
}

void	update_window(t_registry *shell, t_sle *sle)
{
	update_winsize(shell, sle);
	sle->cursor.x = 0;
	sle->cursor.y = 0;
	sle->cursor.index = 0;
}
