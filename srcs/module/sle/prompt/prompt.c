/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/06 14:12:31 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

/*
**	Standart prompt invocation
*/

t_vector	*prompt(t_registry *shell, char *prompt_state)
{
	char	character[READ_SIZE + 1];

	update_window(shell);
	print_prompt(shell, prompt_state);
	ft_bzero(character, READ_SIZE + 1);
	vct_reset(shell->interface.line);
	vct_reset(shell->interface.window.displayed_line);
	while (is_separator(character) == FALSE)
	{
		ft_bzero(character, READ_SIZE);
		if (read(0, character, READ_SIZE) == FAILURE)
			return (NULL);
		handle_input_key(shell, character);
		redraw(shell);
		if (is_eof(vct_get_string(shell->interface.line)) == TRUE)
			break ;
	}
	ft_printf("\n");
//	vct_add(shell->interface.line, '\n');
	return (vct_dup(shell->interface.line));
}

t_vector	*invoke_ps2prompt(t_registry *shell, char *missing)
{
	t_vector	*linesave;

	linesave = shell->interface.line;
	shell->interface.line = shell->interface.sub_line;
	shell->interface.prompt.missing_char = missing;
	prompt(shell, INT_PS2);
	shell->interface.line = linesave;
	if (is_eof(vct_get_string(shell->interface.sub_line)) == TRUE)
		return (NULL);
//	vct_add(shell->interface.sub_line, '\n');
	return (vct_dup(shell->interface.sub_line));
}

t_vector	*invoke_ps3prompt(t_registry *shell)
{
	t_vector	*linesave;

	linesave = shell->interface.line;
	shell->interface.line = shell->interface.sub_line;
	prompt(shell, INT_PS3);
	shell->interface.line = linesave;
	if (is_eof(vct_get_string(shell->interface.sub_line)) == TRUE)
		return (NULL);
//	vct_add(shell->interface.sub_line, '\n');
	return (vct_dup(shell->interface.sub_line));
}
