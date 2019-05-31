/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_interface_struct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 10:14:02 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/31 11:02:41 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <sys/ioctl.h>

uint64_t    init_window(t_registry *shell)
{
    struct winsize	w;
	t_window		*window;

    window = &shell->interface.window;
    if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == FAILURE)
        return (CRITICAL_ERROR | WINDOW_FAIL);

    window->rows = (w.ws_row <= 0) ? 0 : w.ws_row;
	window->cols = (w.ws_col <= 0) ? 0 : w.ws_col;
    window->max_chars = window->rows * window->cols;

    if (add_internal_nbr(shell, INT_COLS, window->cols) == FAILURE)
		return (WINDOW_FAIL | INTERNAL_FAIL);

	if (add_internal_nbr(shell, INT_ROWS, window->rows) == FAILURE)
		return (WINDOW_FAIL | INTERNAL_FAIL);

    if ((window->displayed_line = vct_new(0)) == NULL)
        return (CRITICAL_ERROR | WINDOW_FAIL | VCT_FAIL);

    return (SUCCESS);
}

uint64_t    init_cursor(t_interface *interface)
{
    t_cursor    *cursor;

    cursor = &interface->cursor;
    cursor->x = 0;
    cursor->y = 0;
    cursor->index = 0;
    return (SUCCESS);
}

uint64_t    init_prompt(t_interface *interface)
{
    t_prompt    *prompt;

    prompt = &interface->prompt;
	prompt->length = 0;
	prompt->state = INT_PS1;
    if ((prompt->text = vct_new(0)) == NULL)
        return (PRMPT_FAIL | VCT_FAIL);
    return (SUCCESS);
}
