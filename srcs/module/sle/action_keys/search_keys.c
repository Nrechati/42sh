/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:51:39 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/03 14:52:42 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t		ak_ctrl_t(t_registry *shell, t_sle *sle)
{
	(void)shell;
	if (sle->state != STATE_STD && sle->state != STATE_REVSEARCH)
		return (FAILURE);
	sle->state = STATE_INCSEARCH;
	sle->search_type = NEXT;
	ft_bzero(sle->line->buffer, sle->line->size);
	ft_bzero(sle->sub_line->buffer, sle->sub_line->size);
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	return (SUCCESS);
}

int8_t		ak_ctrl_r(t_registry *shell, t_sle *sle)
{
	(void)shell;
	if (sle->state != STATE_STD && sle->state != STATE_INCSEARCH)
		return (FAILURE);
	sle->state = STATE_REVSEARCH;
	sle->search_type = PREV;
	ft_bzero(sle->line->buffer, sle->line->size);
	ft_bzero(sle->sub_line->buffer, sle->sub_line->size);
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	return (SUCCESS);
}
