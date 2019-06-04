/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_clipboard_paste.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:23:25 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/04 17:23:29 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"


int8_t				ak_paste_clipboard(t_registry *shell)
{
	t_interface *itf;

	itf = &shell->interface;
	if (itf->visual_mode == TRUE)
		return (FALSE);
	vct_insert_string(itf->line, vct_get_string(itf->clip),
					itf->cursor.index);
	set_redraw_flags(&shell->interface, RD_LINE | RD_CMOVE);
	set_cursor_pos(&shell->interface, itf->cursor.index + vct_len(itf->clip));
	return (SUCCESS);
}
