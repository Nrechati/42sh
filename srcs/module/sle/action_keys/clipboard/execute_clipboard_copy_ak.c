/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_clipboard_copy_ak.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:22:59 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/05 13:30:06 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t	ak_copy_selection(t_registry *shell)
{
	char			*tmp;
	t_interface		*itf;
	uint64_t		start;
	uint64_t		length;

	itf = &shell->interface;
	if (itf->visual_mode == FALSE)
		return (FAILURE);
	start = (itf->vis_stop < itf->vis_start) ? itf->vis_stop : itf->vis_start;
	length = (itf->vis_stop < itf->vis_start)
			? (itf->vis_start - itf->vis_stop)
			: (itf->vis_stop - itf->vis_start);
	vct_reset(itf->clip);
	tmp = vct_sub(itf->line, start, length + 1);
	vct_scpy(itf->clip, tmp, ft_strlen(tmp));
	ft_strdel(&tmp);
	ak_exit_visual_mode(shell);
	set_redraw_flags(&shell->interface, RD_LINE | RD_CMOVE);
	set_cursor_pos(&shell->interface, start);
	return (SUCCESS);
}
