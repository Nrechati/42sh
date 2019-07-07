/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_fptp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:45:43 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/07 19:45:44 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	redrawmode_fpte(t_sle *sle)
{
	sle->window.point2 = (sle->rd_info.line_len
					> sle->rd_info.disp_len)
					? sle->rd_info.line_len
					: sle->rd_info.disp_len;
	++sle->window.point2;
	redrawmode_fptp(sle);
}

void	redrawmode_fstp(t_sle *sle)
{
	sle->window.point1 = 0;
	redrawmode_fptp(sle);
}
