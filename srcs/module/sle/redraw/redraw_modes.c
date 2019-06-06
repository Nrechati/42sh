/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_modes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 10:26:30 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/06 15:01:25 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

void	redrawmode_clear(t_registry *shell)
{
	tputs(shell->interface.termcaps.clear, 1, &ft_putc);
	shell->interface.cursor.x = 0;
	shell->interface.cursor.y = 0;
	shell->interface.cursor.index = 0;
	print_prompt(shell, shell->interface.prompt.state);
}

void	redrawmode_last(t_registry *shell)
{
	t_coord		co;
	uint64_t	prompt_len;
	uint64_t 	line_len;
	uint64_t 	disp_len;

	line_len  = vct_len(shell->interface.line);
	disp_len  = vct_len(shell->interface.window.displayed_line);
	prompt_len = get_prompt_length(&shell->interface.prompt);
	if (line_len >= disp_len)
	{
		prompt_len += line_len - 1;
		index_to_coord(&shell->interface, prompt_len, &co);
		move_cursor_to_coord(&shell->interface, co.x, co.y);
		print_char(&shell->interface, vct_charat(shell->interface.line,
						vct_len(shell->interface.line) - 1));
	}
	else
	{
		prompt_len += line_len - 1;
		index_to_coord(&shell->interface, prompt_len, &co);
		move_cursor_to_coord(&shell->interface, co.x, co.y);
		print_char(&shell->interface, ' ');
	}
}

void	redrawmode_line(t_registry *shell)
{
	t_coord		co;
	int64_t		diff;
	uint64_t	prompt_len;

	prompt_len = get_prompt_length(&shell->interface.prompt);
	index_to_coord(&shell->interface, prompt_len, &co);
	move_cursor_to_coord(&shell->interface, co.x, co.y);
	diff = vct_len(shell->interface.line)
			- (vct_len(shell->interface.window.displayed_line));
	print_loop(&shell->interface, vct_get_string(shell->interface.line));
	if (diff <= 0)
	{
		while (++diff <= 0)
			print_char(&shell->interface, ' ');
	}
}

void	redrawmode_fptp(t_registry *shell)
{
	char 		c;
	t_coord		co;
	int64_t		length;
	uint64_t	tmp;

	index_to_coord(&shell->interface, shell->interface.window.point1
						+ get_prompt_length(&shell->interface.prompt), &co);
	move_cursor_to_coord(&shell->interface, co.x, co.y);
	length = shell->interface.window.point2
			- (shell->interface.window.point1 + 1);
//	print_loop(&shell->interface, vct_get_str);
	tmp = shell->interface.window.point1;
	while (length > 0)
	{
		if ((c = vct_charat(shell->interface.line, tmp)) != 0)
			print_char(&shell->interface, c);
		else
			print_char(&shell->interface, ' ');
		++tmp;
		--length;
	}
}

void	redrawmode_fpte(t_registry *shell)
{
	t_interface *itf;
	uint64_t	line_len;
	uint64_t	disp_len;

	itf = &shell->interface;
	line_len = vct_len(itf->line);
	disp_len = vct_len(itf->window.displayed_line);
	itf->window.point2 = (line_len > disp_len) ? line_len : disp_len;
	++itf->window.point2;
	redrawmode_fptp(shell);
}

void	redrawmode_fstp(t_registry *shell)
{
	t_interface *itf;

	itf = &shell->interface;
	itf->window.point1 = 0;
	redrawmode_fptp(shell);
}
