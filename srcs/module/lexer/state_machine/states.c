/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:03:31 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/13 19:59:10 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	number_machine(t_lexer *machine)
{
	if (ft_isdigit(*machine->input->buffer) == TRUE)
	{
		machine->last_lexer = E_IO_NUMBER;
		vct_add(machine->buffer, *machine->input->buffer);
		vct_cut(machine->input);
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

int		assign_detect(t_lexer *machine)
{
	if (machine->assign_detect == ASSIGN_OFF)
		return (0);
	if (*machine->input->buffer != '=')
		return (0);
	if (*machine->buffer->buffer == '\0')
		return (0);
	if (ft_strchr(machine->buffer->buffer, '='))
		return (0);
	machine->last_lexer = E_ASSIGN;
	machine->assign_detect = ASSIGN_NEXT;
	machine->state = L_OUT;
	return (1);
}

void	string_machine(t_lexer *machine)
{
	if (*machine->input->buffer == '\0')
		machine->state = L_START;
	if (ft_strchr(LETTER_INTERUPT, *machine->input->buffer) != NULL)
	{
		if (machine->assign_detect == ASSIGN_NEXT)
			machine->assign_detect = ASSIGN_ON;
		else
			machine->assign_detect = ASSIGN_OFF;
		machine->state = L_OUT;
		return ;
	}
	else if (ft_strchr(LETTER_SPECIAL, *machine->input->buffer) != NULL)
		string_special(machine);
	else if (machine->last_lexer != E_SPSTRING)
		machine->last_lexer = E_STRING;
	if (assign_detect(machine))
		vct_cut(machine->input);
	else if (*machine->input->buffer != '\0')
	{
		vct_add(machine->buffer, *machine->input->buffer);
		vct_cut(machine->input);
	}
}
