/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_he_ak.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:21:43 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/04 17:22:01 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t	ak_home(t_registry *shell)
{
	int64_t	x;

	set_redraw_flags(&shell->interface, RD_NONE | RD_CHOME);
	set_cursor_pos(&shell->interface, 0);
	if (shell->interface.visual_mode == TRUE)
	{
		x = 0;
		while ((shell->interface.cursor.index + x) >= 1)
			shell->interface.vis_stop = (shell->interface.cursor.index + --x);
	}
	return (SUCCESS);
}

int8_t	ak_end(t_registry *shell)
{
	int64_t x;

	set_redraw_flags(&shell->interface, RD_NONE | RD_CEND);
	set_cursor_pos(&shell->interface, vct_len(shell->interface.line));
	if (shell->interface.visual_mode == TRUE)
	{
		x = 0;
		while ((shell->interface.cursor.index + x)
					< vct_len(shell->interface.line))
			shell->interface.vis_stop = (shell->interface.cursor.index + ++x);
	}
	return (SUCCESS);
}
