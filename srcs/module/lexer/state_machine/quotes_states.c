/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 13:34:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/04 17:56:42 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	single_quote_machine(t_lexer *machine)
{
	while (*machine->input->buffer == '\0')
	{
		vct_del(&machine->input);
		machine->input = invoke_ps2prompt(g_shell, "quote");
	}
	if (*machine->input->buffer == '\'')
		machine->state = L_STRING;
	if (*machine->input->buffer != '\0')
	{
		if (create_token_data(machine) == FAILURE)
			return ;
		vct_del_char(machine->input, 0);
	}
	else
		machine->state = L_START;
}

void	double_quote_machine(t_lexer *machine)
{
	while (*machine->input->buffer == '\0')
	{
		vct_del(&machine->input);
		machine->input = invoke_ps2prompt(g_shell, "dquote");
	}
	if (*machine->input->buffer == '\"')
		machine->state = L_STRING;
	if (*machine->input->buffer != '\0')
	{
		if (create_token_data(machine) == FAILURE)
			return ;
		vct_del_char(machine->input, 0);
	}
	else
		machine->state = L_START;
}
