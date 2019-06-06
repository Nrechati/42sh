/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 10:14:06 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/06 14:51:16 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

static void    redraw_line(t_registry *shell)
{
	if (shell->interface.window.rd_flag & RD_NONE)
        return;
	if (shell->interface.window.rd_flag & RD_CLEAR)
	{
		redrawmode_clear(shell);
		shell->interface.window.rd_flag |= RD_LINE;
	}
	if (shell->interface.window.rd_flag & RD_LINE)
		redrawmode_line(shell);
	else if (shell->interface.window.rd_flag & RD_LAST)
		redrawmode_last(shell);
	else if (shell->interface.window.rd_flag & RD_FPTE)
    	redrawmode_fpte(shell);
	else if (shell->interface.window.rd_flag & RD_FSTP)
		redrawmode_fstp(shell);
	else if (shell->interface.window.rd_flag & RD_FPTP)
		redrawmode_fptp(shell);
}
static inline void reset_redraw_mode(t_interface *itf)
{
	vct_reset(itf->window.displayed_line);
	vct_ncpy(itf->window.displayed_line, itf->line,
					vct_len(itf->line));
	itf->window.rd_flag = 0;
	itf->window.point1 = 0;
	itf->window.point2 = 0;
	itf->window.point_cursor = 0;
}

void    redraw(t_registry *shell)
{
	redraw_line(shell);
	if (shell->interface.visual_mode == TRUE)
		redrawmode_visual(shell);
	move_cursor(shell);

	reset_redraw_mode(&shell->interface);
}

inline void		add_redraw_flags(t_interface *itf, uint32_t rd_flag)
{
	itf->window.rd_flag |= rd_flag;
}

inline void     set_redraw_flags(t_interface *itf, uint32_t rd_flag)
{
	itf->window.rd_flag = rd_flag;
}

inline void     set_redraw_bounds(t_interface *itf, uint64_t start, uint64_t end)
{
	itf->window.point1 = start;
	itf->window.point2 = end;
}

inline void     set_cursor_pos(t_interface *itf, uint64_t index)
{
	itf->window.point_cursor = index;
}
