/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_fptp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:51:27 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/03 15:51:41 by nrechati         ###   ########.fr       */
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
