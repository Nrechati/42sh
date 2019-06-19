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

static void	subprompt_calling(t_lexer *machine, uint64_t option)
{
	t_vector	*new_input;

	new_input = vct_new(0);
	while (new_input->buffer[0] == '\0')
		sle(g_shell, &new_input, option);
	vct_ncat(machine->input, new_input, vct_len(new_input));
	vct_del(&new_input);
}

void	single_quote_machine(t_lexer *machine)
{
	if (g_shell->option.option & INTERACTIVE_OPT)
	{
		if (machine->input->buffer[machine->index] == '\0')
			subprompt_calling(machine, SLE_PS2_PROMPT | PRINT_QUOTE);
		if (machine->input->buffer[machine->index] == '\'')
			machine->state = L_STRING;
		if (machine->input->buffer[machine->index] != '\0')
		{
			vct_add(machine->buffer, machine->input->buffer[machine->index]);
			machine->index++;
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
		if (machine->input->buffer[machine->index] == '\0')
			subprompt_calling(machine, SLE_PS2_PROMPT | PRINT_DQUOTE);
		if (machine->input->buffer[machine->index] == '\"')
			machine->state = L_STRING;
		if (machine->input->buffer[machine->index] != '\0')
		{
			vct_add(machine->buffer, machine->input->buffer[machine->index]);
			machine->index++;
		}	
		else
			machine->state = L_START;
	}
	else
		machine->state = L_OUT;
}
