/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 13:34:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/18 16:29:24 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	single_quote_machine(t_lexer *machine)
{
	if (g_shell->option.option & INTERACTIVE_OPT)
	{
		while (*machine->input->buffer == '\0')
		{
			vct_del(&machine->input);
			sle(g_shell, &machine->input, SLE_PS2_PROMPT | PRINT_QUOTE);
			if (*machine->input->buffer != '\0')
				vct_ncat(machine->origin_input, machine->input,
						vct_len(machine->input));
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
	else
		machine->state = L_OUT;
}

void	double_quote_machine(t_lexer *machine)
{
	if (g_shell->option.option & INTERACTIVE_OPT)
	{
		while (*machine->input->buffer == '\0')
		{
			vct_del(&machine->input);
			sle(g_shell, &machine->input, SLE_PS2_PROMPT | PRINT_DQUOTE);
			if (*machine->input->buffer != '\0')
				vct_ncat(machine->origin_input, machine->input,
						vct_len(machine->input));
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
	else
		machine->state = L_OUT;
}
