/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:56:27 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/20 18:10:07 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static uint8_t	cmp_buf_and_input(t_lexer *machine, char c)
{
	if (get_input(machine, CUR_CHAR) == c && get_buffer(machine, CUR_CHAR) == c)
		return (TRUE);
	return (FALSE);
}

void			double_sign_machine(t_lexer *machine)
{
	if (ft_strchr(DOUBLE_SIGN, get_input(machine, CUR_CHAR))!= NULL)
	{
		if (cmp_buf_and_input(machine, '|') == TRUE)
			machine->last_lexer = E_OR;
		else if (cmp_buf_and_input(machine, ';') == TRUE)
			machine->last_lexer = E_DSEMI;
		else if (cmp_buf_and_input(machine, '&') == TRUE)
			machine->last_lexer = E_DAND;
		else if (cmp_buf_and_input(machine, '=') == TRUE)
			machine->last_lexer = E_DEQ;
		else if (get_buffer(machine, CUR_CHAR) == '!'
				&& get_input(machine, CUR_CHAR) == '=')
			machine->last_lexer = E_NOTEQ;
		machine->index++;
	}
	if (get_buffer(machine, CUR_CHAR) == '='
			&& get_input(machine, CUR_CHAR) != '=')
		machine->state = L_STRING;
	else
		machine->state = L_OUT;
	if (machine->last_lexer == E_DAND || machine->last_lexer == E_OR)
		machine->assign_detect = ASSIGN_ON;
}

static uint8_t	double_dispatcher(t_lexer *machine)
{
	if (get_input(machine, CUR_CHAR) == '>')
		machine->state = L_GREATER;
	else if (get_input(machine, CUR_CHAR) == '<')
		machine->state = L_LESSER;
	else if (ft_strchr(DOUBLE_SIGN, get_input(machine, CUR_CHAR)) != NULL)
		machine->state = L_DSIGN;
	else
		return (FALSE);
	return (TRUE);
}

void			and_machine(t_lexer *machine)
{
	if (get_input(machine, NEXT_CHAR) == '>')
	{
		machine->index += 2;
		if (get_input(machine, CUR_CHAR) == '>')
			machine->last_lexer = E_ANDDGREAT;
		else
			machine->last_lexer = E_ANDGREAT;
		machine->index++;
	}
	else
	{
		machine->assign_detect = ASSIGN_ON;
		add_to_buffer(machine);
	}
	machine->state = L_OUT;
}

void			sign_machine(t_lexer *machine)
{
	if (get_input(machine, CUR_CHAR) == '\'')
		machine->state = L_SQTE;
	else if (get_input(machine, CUR_CHAR) == '\"')
		machine->state = L_DQTE;
	else if (get_input(machine, CUR_CHAR) == '&'
			&& get_input(machine, NEXT_CHAR) != '&')
		machine->state = L_AND;
	else if (double_dispatcher(machine) != FALSE)
		add_to_buffer(machine);
	else
	{
		add_to_buffer(machine);
		machine->assign_detect = ASSIGN_ON;
		machine->state = L_OUT;
	}
}
