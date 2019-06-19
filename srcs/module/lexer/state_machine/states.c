/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:03:31 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/17 15:40:55 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	number_machine(t_lexer *machine)
{
	if (ft_isdigit(machine->input->buffer[machine->index]) == TRUE)
	{
		machine->last_lexer = E_IO_NUMBER;
		vct_add(machine->buffer, machine->input->buffer[machine->index]);
		machine->index++;
	}
	else if (ft_strchr("<>", machine->input->buffer[machine->index]) != NULL)
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
	if (machine->input->buffer[machine->index] == '\"')
		machine->state = L_DQTE;
	else if (machine->input->buffer[machine->index] == '\'')
		machine->state = L_SQTE;
}

int		assign_detect(t_lexer *machine)
{
	if (machine->assign_detect == ASSIGN_OFF)
		return (FALSE);
	if (machine->input->buffer[machine->index] != '=')
		return (FALSE);
	if (*machine->buffer->buffer == '\0')
		return (FALSE);
	if (ft_strchr(machine->buffer->buffer, '=') != NULL)
		return (FALSE);
	machine->last_lexer = E_ASSIGN;
	machine->assign_detect = ASSIGN_NEXT;
	machine->state = L_OUT;
	return (TRUE);
}

int		assign_special(t_lexer *machine)
{
	if (machine->assign_detect == ASSIGN_NEXT
			&& *machine->buffer->buffer == '\0')
		return (TRUE);
	return (FALSE);
}
void	string_machine(t_lexer *machine)
{
	if (machine->input->buffer[machine->index] == '\0')
	{
		if (*machine->buffer->buffer == '\0'
				&& machine->assign_detect == ASSIGN_NEXT)
		{
			vct_add(machine->buffer, ' ');
			machine->last_lexer = E_STRING;
			machine->state = L_OUT;
		}
		else
			machine->state = L_START;
		machine->assign_detect = ASSIGN_ON;
	}
	if (ft_strchr(LETTER_INTERUPT,
				machine->input->buffer[machine->index]) != NULL)
	{
		if (machine->assign_detect == ASSIGN_NEXT)
			machine->assign_detect = ASSIGN_ON;
		else
			machine->assign_detect = ASSIGN_OFF;
		machine->state = L_OUT;
		return ;
	}
	else if (ft_strchr(LETTER_SPECIAL,
				machine->input->buffer[machine->index]) != NULL)
	{
		string_special(machine);
		return ;
	}
	else if (machine->last_lexer != E_SPSTRING)
		machine->last_lexer = E_STRING;
	if (assign_detect(machine))
		machine->index++;
	else if (machine->input->buffer[machine->index] != '\0')
	{
		vct_add(machine->buffer, machine->input->buffer[machine->index]);
		machine->index++;
	}
}
