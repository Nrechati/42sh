/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 09:41:12 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/27 09:41:59 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "interface_functions.h"
#include <sys/ioctl.h>

uint64_t	update_winsize(t_registry *shell)
{
	struct winsize w;
	t_window		*win;

    win = &shell->interface.window;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == FAILURE)
        return (CRITICAL_ERROR | WINDOW_FAIL);

	win->rows = (w.ws_row <= 0) ? 0 : w.ws_row;
	win->cols = (w.ws_col <= 0) ? 0 : w.ws_col;
    win->max_chars = win->rows * win->cols;

    if (add_internal_nbr(shell, INT_COLS, win->cols) == FAILURE)
		return (WINDOW_FAIL | INTERNAL_FAIL);

	if (add_internal_nbr(shell, INT_ROWS, win->rows) == FAILURE)
		return (WINDOW_FAIL | INTERNAL_FAIL);

	return (SUCCESS);
}

void	update_window(t_registry *shell)
{
	update_winsize(shell);

	shell->interface.cursor.x = 0;
	shell->interface.cursor.y = 0;
	shell->interface.cursor.index = 0;
}


