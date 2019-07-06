/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:16:26 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/06 15:58:04 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static uint8_t		is_input_valid(uint8_t valid)
{
	if (valid != SUCCESS && valid != LINE_FAIL)
		return (FALSE);
	return (TRUE);
}

static uint8_t		is_only_whitespaces(t_vector *input)
{
	size_t		i;

	if (input == NULL || input->buffer == NULL)
		return (TRUE);
	i = 0;
	while (input->buffer[i] != '\0')
	{
		if (input->buffer[i] != '\t' && input->buffer[i] != '\n'
				&& input->buffer[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void				interactive_mode(t_registry *shell)
{
	t_vector		*input;

	input = NULL;
	load_signal_profile(SLE_PROFILE);
	while (is_input_valid(sle(shell, &input, SLE_GET_INPUT)) == TRUE)
	{
		if (is_only_whitespaces(input) == FALSE)
		{
			term_mode(TERMMODE_DFLT);
			load_signal_profile(DFLT_PROFILE);
			execution_pipeline(shell, &input);
			load_signal_profile(SLE_PROFILE);
		}
		else if (input != NULL && input->buffer != NULL)
			history(g_shell, vct_get_string(input), ADD_ENTRY);
		vct_del(&input);
	}
	vct_del(&input);
	term_mode(TERMMODE_DFLT);
	if (exit_blt(shell, NULL) == SUCCESS)
		interactive_mode(shell);
	shell_exit_routine(shell, SUCCESS);
}
