/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:56:27 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/04 17:56:28 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void			double_sign_machine(t_lexer *machine)
{
	uint32_t	checker;

	checker = 0;
	if (ft_strchr(DOUBLE_SIGN, *machine->input->buffer) != NULL)
	{
		if (*machine->buffer->buffer == '|'
				&& *machine->input->buffer == '|' && ++checker)
			machine->last_lexer = E_OR;
		else if (*machine->buffer->buffer == ';'
				&& *machine->input->buffer == ';' && ++checker)
			machine->last_lexer = E_DSEMI;
		else if (*machine->buffer->buffer == '&'
				&& *machine->input->buffer == '&' && ++checker)
			machine->last_lexer = E_DAND;
		else if (*machine->buffer->buffer == '='
				&& *machine->input->buffer == '=' && ++checker)
			machine->last_lexer = E_DEQ;
		else if (*machine->buffer->buffer == '!'
				&& *machine->input->buffer == '=' && ++checker)
			machine->last_lexer = E_NOTEQ;
		if (checker != FALSE)
			vct_del_char(machine->input, 0);
	}
	if (*machine->buffer->buffer == '=' && *machine->input->buffer != '=')
		machine->state = L_STRING;
	else
		machine->state = L_OUT;
}

static uint32_t	double_dispatcher(t_lexer *machine)
{
	uint32_t	checker;

	checker = 0;
	if (*machine->input->buffer == '>')
	{
		++checker;
		machine->state = L_GREATER;
	}
	else if (*machine->input->buffer == '<')
	{
		++checker;
		machine->state = L_LESSER;
	}
	else if (ft_strchr(DOUBLE_SIGN, *machine->input->buffer) != NULL)
	{
		++checker;
		machine->state = L_DSIGN;
	}
	return (checker);
}

void			and_machine(t_lexer *machine)
{
	if (machine->input->buffer[1] == '>')
	{
		vct_del_char(machine->input, 0);
		machine->last_lexer = E_ANDGREAT;
		vct_del_char(machine->input, 0);
		if (machine->last_lexer == E_ANDGREAT && *machine->input->buffer == '>')
		{
			machine->last_lexer = E_ANDDGREAT;
			vct_del_char(machine->input, 0);
		}
	}
	else
	{
		if (create_token_data(machine) == FAILURE)
			return ;
		vct_del_char(machine->input, 0);
	}
	machine->state = L_OUT;
}

void			sign_machine(t_lexer *machine)
{
	if (*machine->input->buffer == '\'')
		machine->state = L_SQTE;
	else if (*machine->input->buffer == '\"')
		machine->state = L_DQTE;
	else if (*machine->input->buffer == '&')
	{
		machine->state = L_AND;
		return ;
	}
	else if (double_dispatcher(machine) != FALSE)
	{
		if (create_token_data(machine) == FAILURE)
			return ;
	}
	else
	{
		if (create_token_data(machine) == FAILURE)
			return ;
		machine->state = L_OUT;
	}
	vct_del_char(machine->input, 0);
}
