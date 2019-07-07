/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_clipboard_paste.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:37:18 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/07 19:37:19 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t				ak_paste_clipboard(t_registry *shell, t_sle *sle)
{
	(void)shell;
	if (sle->state != STATE_STD)
		return (FALSE);
	vct_insert_string(sle->line, vct_get_string(sle->clip),
					sle->cursor.index);
	set_redraw_flags(sle, RD_LINE | RD_CMOVE);
	set_cursor_pos(sle, sle->cursor.index + vct_len(sle->clip));
	find_multiline_coord(sle, vct_len(sle->clip));
	return (SUCCESS);
}
