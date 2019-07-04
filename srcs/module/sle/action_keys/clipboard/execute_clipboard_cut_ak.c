/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_clipboard_cut_ak.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:23:11 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/03 14:42:19 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t				ak_cut_selection(t_registry *shell, t_sle *sle)
{
	char			*tmp;
	uint64_t		start;
	uint64_t		length;

	if (sle->state != STATE_VISUAL)
		return (FAILURE);
	start = (sle->vis_stop < sle->vis_start) ? sle->vis_stop : sle->vis_start;
	length = (sle->vis_stop < sle->vis_start)
			? (sle->vis_start - sle->vis_stop)
			: (sle->vis_stop - sle->vis_start);
	vct_reset(sle->clip);
	tmp = vct_sub(sle->line, start, length);
	vct_scpy(sle->clip, tmp, ft_strlen(tmp));
	ft_strdel(&tmp);
	if (start == 0 && length == vct_len(sle->line))
		vct_reset(sle->line);
	else
		vct_del_string(sle->line, start, length);
	ak_exit_modes(shell, sle);
	set_redraw_flags(sle, RD_LINE | RD_CMOVE);
	set_cursor_pos(sle, start);
	return (SUCCESS);
}
