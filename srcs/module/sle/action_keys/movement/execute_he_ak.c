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

int8_t	ak_home(t_sle *sle)
{
	int64_t	x;

	set_redraw_flags(sle, RD_NONE | RD_CHOME);
	set_cursor_pos(sle, 0);
	if (sle->visual_mode == TRUE)
	{
		x = 0;
		while ((sle->cursor.index + x) >= 1)
			sle->vis_stop = (sle->cursor.index + --x);
	}
	return (SUCCESS);
}

int8_t	ak_end(t_sle *sle)
{
	int64_t x;

	set_redraw_flags(sle, RD_NONE | RD_CEND);
	set_cursor_pos(sle, vct_len(sle->line));
	if (sle->visual_mode == TRUE)
	{
		x = 0;
		while ((sle->cursor.index + x)
					< vct_len(sle->line))
			sle->vis_stop = (sle->cursor.index + ++x);
	}
	return (SUCCESS);
}
