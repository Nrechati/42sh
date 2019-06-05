/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:03:31 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/04 17:56:18 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	number_machine(t_lexer *machine)
{
	if (ft_isdigit(*machine->input->buffer) == TRUE)
	{
		machine->last_lexer = E_IO_NUMBER;
		if (create_token_data(machine) == FAILURE)
			return ;
		vct_del_char(machine->input, 0);
	}
	else if (ft_strchr("<>", *machine->input->buffer) != NULL)
		machine->state = L_OUT;
	else
	{
		machine->last_lexer = E_STRING;
		machine->state = L_STRING;
	}
}

void	string_special(t_lexer *machine)
{
	machine->last_lexer = E_SPSTRING;
	if (*machine->input->buffer == '\"')
		machine->state = L_DQTE;
	else if (*machine->input->buffer == '\'')
		machine->state = L_SQTE;
}

void	string_machine(t_lexer *machine)
{
	if (*machine->input->buffer == '\0')
		machine->state = L_START;
	if (ft_strchr(LETTER_INTERUPT, *machine->input->buffer) != NULL)
	{
		machine->state = L_OUT;
		return ;
	}
	else if (ft_strchr(LETTER_SPECIAL, *machine->input->buffer) != NULL)
		string_special(machine);
	else if (machine->last_lexer != E_SPSTRING)
		machine->last_lexer = E_STRING;
	if (*machine->input->buffer != '\0')
	{
		if (create_token_data(machine) == FAILURE)
			return ;
		vct_del_char(machine->input, 0);
	}
}
