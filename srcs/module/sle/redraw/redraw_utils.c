/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:46:31 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/07 19:46:32 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

inline void		add_redraw_flags(t_sle *sle, uint32_t rd_flag)
{
	sle->window.rd_flag |= rd_flag;
}

inline void		set_redraw_flags(t_sle *sle, uint32_t rd_flag)
{
	sle->window.rd_flag = rd_flag;
}

inline void		set_redraw_bounds(t_sle *sle, uint64_t start, uint64_t end)
{
	sle->window.point1 = start;
	sle->window.point2 = end;
}

inline void		set_cursor_pos(t_sle *sle, uint64_t index)
{
	sle->window.point_cursor = index;
}
