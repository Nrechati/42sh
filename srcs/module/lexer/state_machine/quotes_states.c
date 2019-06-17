/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 13:34:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/17 14:23:02 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	single_quote_machine(t_lexer *machine)
{
	while (*machine->input->buffer == '\0')
	{
		vct_del(&machine->input);
		sle(g_shell, &machine->input, SLE_PS2_PROMPT | PRINT_QUOTE);
	}
	if (*machine->input->buffer == '\'')
		machine->state = L_STRING;
	if (*machine->input->buffer != '\0')
	{
		vct_add(machine->buffer, *machine->input->buffer);
		vct_cut(machine->input);
	}
	else
		machine->state = L_START;
}

void	double_quote_machine(t_lexer *machine)
{
	while (*machine->input->buffer == '\0')
	{
		vct_del(&machine->input);
		sle(g_shell, &machine->input, SLE_PS2_PROMPT | PRINT_DQUOTE);
	}
	if (*machine->input->buffer == '\"')
		machine->state = L_STRING;
	if (*machine->input->buffer != '\0')
	{
		vct_add(machine->buffer, *machine->input->buffer);
		vct_cut(machine->input);
	}
	else
		machine->state = L_START;
}
