/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_special_ak.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:14:28 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/29 18:52:29 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t		tc_ak_hightab(t_registry *shell)
{
	(void)shell;
	return (SUCCESS);
}

int8_t		tc_ak_delete(t_registry *shell)
{
	if (validate_interface_content(&shell->interface) == FAILURE)
		return (FAILURE);
	shift_content_left_once(shell->interface.line,
			shell->interface.cursor.index);
	redraw_after_cursor(shell);
	return (SUCCESS);
}

int8_t		tc_ak_backspace(t_registry *shell)
{
	t_interface	*itf;

	itf = &shell->interface;
	if (validate_interface_content(itf) == FAILURE)
		return (FAILURE);
	if (itf->cursor.index == 0)
		return (SUCCESS);
	tc_ak_arrow_left(shell);
	shift_content_left_once(itf->line, itf->cursor.index);
	redraw_after_cursor(shell);
	return (SUCCESS);
}
