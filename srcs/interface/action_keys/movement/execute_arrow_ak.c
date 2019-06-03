/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_arrow_ak.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:12:56 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/03 09:55:44 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"

int8_t				ak_arrow_right(t_registry *shell)
{
	set_redraw_flags(&shell->interface, RD_NONE | RD_CMOVE);


	int8_t offset;
	offset = 1;
	if (shell->interface.cursor.index >= vct_len(shell->interface.line))
			offset = 0;
	if (shell->interface.visual_mode == TRUE)
	{
		shell->interface.vis_stop = shell->interface.cursor.index + offset;
//		add_redraw_flags(&shell->interface, RD_);
	}

	set_redraw_flags(&shell->interface, RD_NONE | RD_CMOVE);
	set_cursor_pos(&shell->interface, shell->interface.cursor.index + offset);
	return (SUCCESS);
}

int8_t				ak_arrow_left(t_registry *shell)
{
	set_redraw_flags(&shell->interface, RD_NONE | RD_CMOVE);


	int8_t offset;
	offset = 1;
	if (shell->interface.cursor.index == 0)
			offset = 0;

	if (shell->interface.visual_mode == TRUE
		&& shell->interface.cursor.index > 0)
		shell->interface.vis_stop = shell->interface.cursor.index - offset;

	set_cursor_pos(&shell->interface, shell->interface.cursor.index - offset);
	return (SUCCESS);
}

int8_t				ak_arrow_up(__unused t_registry *shell)
{
//	ft_printf("%c[%d;%df",0x1B, 0, 0);
	return (FAILURE);
}

int8_t				ak_arrow_down(__unused t_registry *shell)
{
//	char *position = ft_strnew(9);
//	ft_printf("|len:%d|\n", vct_len(shell->interface.line));
//	ft_dprintf(STDOUT_FILENO, "%c[6n", 0x1B);
//	read(STDOUT_FILENO, position, 8);
//	ft_printf("Position response: |%s|\n", position);
	return (FAILURE);
}
