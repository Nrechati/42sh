/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_clipboard_paste.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:23:25 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/20 10:57:25 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"


int8_t				ak_paste_clipboard(__unused t_registry *shell, t_sle *sle)
{
	if (sle->state != STATE_STD)
		return (FALSE);
	vct_insert_string(sle->line, vct_get_string(sle->clip),
					sle->cursor.index);
	set_redraw_flags(sle, RD_LINE | RD_CMOVE);
	set_cursor_pos(sle, sle->cursor.index + vct_len(sle->clip));
	return (SUCCESS);
}
