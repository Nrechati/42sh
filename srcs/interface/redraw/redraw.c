/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 10:14:06 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/03 13:42:04 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>
#include "log.h"
#include "interface_functions.h"

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
    {
		shell->interface.window.rd_flag &= ~RD_FPTE;
		shell->interface.window.rd_flag |= RD_FPTP;

//		shell->interface.window.point2 =
//				(line_len >= disp_len) ? line_len + 1 : disp_len + 1;
    }
	else if (shell->interface.window.rd_flag & RD_FSTP)
    {
//		rd_flag &= ~RD_FSTP;
//		rd_flag |= RD_FPTP;
//		shell->interface.window.point1 = 0;
    }

	if (shell->interface.window.rd_flag & RD_FPTP)
		redrawmode_fptp(shell);
}

void    redraw(t_registry *shell)
{
	ft_dprintf(3, "\n\n");
	redraw_line(shell);

	if (shell->interface.visual_mode == TRUE)
		redrawmode_visual(shell);

	move_cursor(shell);

	vct_reset(shell->interface.window.displayed_line);
	vct_ncpy(shell->interface.window.displayed_line, shell->interface.line,
					vct_len(shell->interface.line));

	shell->interface.window.rd_flag = 0;
	shell->interface.window.point1 = 0;
	shell->interface.window.point2 = 0;
	shell->interface.window.point_cursor = 0;
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
