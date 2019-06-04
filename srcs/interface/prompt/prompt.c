/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <skuppers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/04 14:22:30 by ffoissey         ###   ########.fr       */
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

//	overwrite_protection(shell);
	return (vct_dup(shell->interface.line));
}

/*
** ------------------------------------------------------------------ |
**	Sub prompt invokation.
**	Returns an allocated vector
**	Return NULL on read error, eof, or dup error(malloc)
*/
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

	return (vct_dup(shell->interface.sub_line));
}
