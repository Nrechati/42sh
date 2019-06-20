/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:03:31 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/20 18:07:47 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	number_machine(t_lexer *machine)
{
	if (ft_isdigit(get_input(machine, CUR_CHAR)) == TRUE)
	{
		machine->last_lexer = E_IO_NUMBER;
		add_to_buffer(machine);
	}
	else if (ft_strchr("<>", get_input(machine, CUR_CHAR)) != NULL)
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
	if (get_input(machine, CUR_CHAR) == '\"')
		machine->state = L_DQTE;
	else if (get_input(machine, CUR_CHAR) == '\'')
		machine->state = L_SQTE;
}

int		assign_detect(t_lexer *machine)
{
	if (machine->assign_detect == ASSIGN_OFF)
		return (FALSE);
	if (get_input(machine, CUR_CHAR) != '=')
		return (FALSE);
	if (get_buffer(machine, CUR_CHAR) == '\0')
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
		&& get_buffer(machine, CUR_CHAR) == '\0')
		return (TRUE);
	return (FALSE);
}

void	string_machine(t_lexer *machine)
{
	if (get_input(machine, CUR_CHAR) == '\0')
	{
		if (get_buffer(machine, CUR_CHAR) == '\0'
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
	else if (get_input(machine, CUR_CHAR) == '\\')
	{
		machine->index++;
		add_to_buffer(machine);
		machine->last_lexer = E_STRING;
		machine->state = L_STRING;
	}
	if (ft_strchr(LETTER_INTERUPT, get_input(machine, CUR_CHAR)) != NULL)
	{
		if (machine->assign_detect == ASSIGN_NEXT)
			machine->assign_detect = ASSIGN_ON;
		else
			machine->assign_detect = ASSIGN_OFF;
		machine->state = L_OUT;
		return ;
	}
	else if (ft_strchr(LETTER_SPECIAL, get_input(machine, CUR_CHAR)) != NULL)
		string_special(machine);
	else if (machine->last_lexer != E_SPSTRING)
		machine->last_lexer = E_STRING;
	if (assign_detect(machine))
		machine->index++;
	else if (get_input(machine, CUR_CHAR) != '\0')
		add_to_buffer(machine);
}
