/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sle_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:44:56 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/07 19:44:57 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <sys/ioctl.h>

uint64_t	init_window(t_sle *sle)
{
	struct winsize	w;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == FAILURE)
		return (CRITICAL_ERROR | WINDOW_FAIL);
	sle->window.rows = (w.ws_row <= 0) ? 1 : w.ws_row;
	sle->window.cols = (w.ws_col <= 0) ? 1 : w.ws_col;
	if ((sle->window.displayed_line = vct_new(0)) == NULL)
		return (CRITICAL_ERROR | LINE_FAIL);
	return (SUCCESS);
}

uint64_t	init_cursor(t_sle *sle)
{
	sle->cursor.x = 0;
	sle->cursor.y = 0;
	sle->cursor.index = 0;
	return (SUCCESS);
}

uint64_t	init_prompt(t_sle *sle)
{
	sle->prompt.length = 0;
	sle->prompt.state = INT_PS1;
	sle->prompt.missing_char = NULL;
	return (SUCCESS);
}
