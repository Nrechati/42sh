/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <skuppers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/27 10:16:11 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"
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

	while (!is_separator(character))
	{
		ft_bzero(character, READ_SIZE);
		if (read(0, character, READ_SIZE) == FAILURE)
			return (NULL);

		handle_input_key(shell, character);
		redraw(shell);

		if (is_eof(vct_get_string(shell->interface.line)))
			break ;
	}

//	overwrite_protection(shell);
	return (vct_dup(shell->interface.line));
}

/*
**	Sub prompt invokation.
**	Prompt_state is between INT_PS1 & INT_PS4, missing is \m
**	Returns an allocated vector
**	Return NULL on read error, eof, or dup error(malloc)
*/
t_vector	*invoke_ps2prompt(t_registry *shell, char *missing)
{
	t_vector	*linesave;
	(void)missing;
	linesave = shell->interface.line;
	shell->interface.line = shell->interface.sub_line;


	prompt(shell, INT_PS2);

	shell->interface.line = linesave;

	if (is_eof(vct_get_string(shell->interface.sub_line)))
		return (NULL);

	return (vct_dup(shell->interface.sub_line));
}
