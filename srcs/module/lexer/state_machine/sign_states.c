/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:56:27 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/17 14:14:00 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static uint8_t	cmp_buf_and_input(t_lexer *machine, char c)
{
	if (*machine->buffer->buffer == c && *machine->input->buffer == c)
		return (TRUE);
	return (FALSE);
}

void			double_sign_machine(t_lexer *machine)
{
	if (ft_strchr(DOUBLE_SIGN, *machine->input->buffer) != NULL)
	{
		if (cmp_buf_and_input(machine, '|') == TRUE)
			machine->last_lexer = E_OR;
		else if (cmp_buf_and_input(machine, ';') == TRUE)
			machine->last_lexer = E_DSEMI;
		else if (cmp_buf_and_input(machine, '&') == TRUE)
			machine->last_lexer = E_DAND;
		else if (cmp_buf_and_input(machine, '=') == TRUE)
			machine->last_lexer = E_DEQ;
		else if (*machine->buffer->buffer == '!'
				&& *machine->input->buffer == '=')
			machine->last_lexer = E_NOTEQ;
		vct_cut(machine->input);
	}
	if (*machine->buffer->buffer == '=' && *machine->input->buffer != '=')
		machine->state = L_STRING;
	else
		machine->state = L_OUT;
	if (machine->last_lexer == E_DAND || machine->last_lexer == E_OR)
		machine->assign_detect = ASSIGN_ON;
}

static uint8_t	double_dispatcher(t_lexer *machine)
{
	if (*machine->input->buffer == '>')
		machine->state = L_GREATER;
	else if (*machine->input->buffer == '<')
		machine->state = L_LESSER;
	else if (ft_strchr(DOUBLE_SIGN, *machine->input->buffer) != NULL)
		machine->state = L_DSIGN;
	else
		return (FALSE);
	return (TRUE);
}

void			and_machine(t_lexer *machine)
{
	if (machine->input->buffer[1] == '>')
	{
		vct_cut(machine->input);
		machine->last_lexer = E_ANDGREAT;
		vct_cut(machine->input);
		if (machine->last_lexer == E_ANDGREAT && *machine->input->buffer == '>')
			machine->last_lexer = E_ANDDGREAT;
	}
	else
	{
		machine->assign_detect = ASSIGN_ON;
		vct_add(machine->buffer, *machine->input->buffer);
	}
	vct_cut(machine->input);
	machine->state = L_OUT;
}

void			sign_machine(t_lexer *machine)
{
	if (*machine->input->buffer == '\'')
		machine->state = L_SQTE;
	else if (*machine->input->buffer == '\"')
		machine->state = L_DQTE;
	else if (machine->input->buffer[0] == '&'
			&& machine->input->buffer[1] != '&')
	{
		machine->state = L_AND;
		return ;
	}
	else if (double_dispatcher(machine) != FALSE)
		vct_add(machine->buffer, *machine->input->buffer);
	else
	{
		vct_add(machine->buffer, *machine->input->buffer);
		machine->assign_detect = ASSIGN_ON;
		machine->state = L_OUT;
	}
	vct_cut(machine->input);

}
