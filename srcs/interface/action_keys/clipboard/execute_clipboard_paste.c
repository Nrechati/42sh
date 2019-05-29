/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_clipboard_ak.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:45:51 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/29 08:26:28 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "interface_functions.h"

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
