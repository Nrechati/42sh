/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 10:14:06 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/19 19:00:37 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

static void    redraw_line(t_registry *shell, t_sle *sle)
{
	if (sle->state == STATE_SEARCH)
		sle->window.rd_flag = RD_LINE | RD_CEND;

	if (sle->window.rd_flag & RD_NONE)
        return;
	if (sle->window.rd_flag & RD_CLEAR)
	{
		redrawmode_clear(shell, sle);
		sle->window.rd_flag |= RD_LINE;
	}
	if (sle->window.rd_flag & RD_LINE)
		redrawmode_line(sle);

	else if (sle->window.rd_flag & RD_LAST)
		redrawmode_last(sle);
	else if (sle->window.rd_flag & RD_FPTE)
    	redrawmode_fpte(sle);
	else if (sle->window.rd_flag & RD_FSTP)
		redrawmode_fstp(sle);
	else if (sle->window.rd_flag & RD_FPTP)
		redrawmode_fptp(sle);
}

static inline void reset_redraw_mode(t_sle *sle)
{
	vct_reset(sle->window.displayed_line);
	vct_ncpy(sle->window.displayed_line, sle->line,
					vct_len(sle->line));
	sle->window.rd_flag = 0;
	sle->window.point1 = 0;
	sle->window.point2 = 0;
	sle->window.point_cursor = 0;
}

void	compute_redrawinfo(t_sle *sle, t_redrawinfo *rd_info)
{
	ft_memset(rd_info, 0, sizeof(t_redrawinfo));
	rd_info->line_len = vct_len(sle->line);
	rd_info->disp_len = vct_len(sle->window.displayed_line);
	rd_info->prompt_len = get_prompt_length(&sle->prompt);
	if (sle->window.cols > 0)
	{
		rd_info->lines_amount = ((rd_info->line_len + rd_info->prompt_len)
				/ (sle->window.cols)) + 1;
	}
	sle->rd_info = *rd_info;
}

void    redraw(t_registry *shell, t_sle *sle)
{
	t_redrawinfo	rd_info;

	compute_redrawinfo(sle, &rd_info);
	redraw_line(shell, sle);

	if (sle->state == STATE_VISUAL)
		redrawmode_visual(sle);

	move_cursor(sle);
	reset_redraw_mode(sle);
}

inline void		add_redraw_flags(t_sle *sle, uint32_t rd_flag)
{
	sle->window.rd_flag |= rd_flag;
}

inline void     set_redraw_flags(t_sle *sle, uint32_t rd_flag)
{
	sle->window.rd_flag = rd_flag;
}

inline void     set_redraw_bounds(t_sle *sle, uint64_t start, uint64_t end)
{
	sle->window.point1 = start;
	sle->window.point2 = end;
}

inline void     set_cursor_pos(t_sle *sle, uint64_t index)
{
	sle->window.point_cursor = index;
}
