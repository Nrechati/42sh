/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_states.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:23:05 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/13 18:59:11 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		lesser_machine(t_lexer *machine)
{
	if (machine->last_lexer == E_DLESS
			&& get_input(machine, CUR_CHAR) == '-')
		machine->last_lexer = E_DLESSDASH;
	else if (get_buffer(machine, CUR_CHAR) == '<')
	{
		if (get_input(machine, CUR_CHAR) == '<'
			&& get_input(machine, NEXT_CHAR) != '&'
			&& machine->last_lexer != E_DLESS)
		{
			machine->last_lexer = E_DLESS;
			add_to_buffer(machine);
			machine->state = L_OUT;
			return ;
		}
		else if (get_input(machine, CUR_CHAR) == '>')
			machine->last_lexer = E_LESSGREAT;
		else if (get_input(machine, CUR_CHAR) == '&')
			machine->state = L_LESSAND;
		else
		{
			machine->state = L_OUT;
			return ;
		}
	}
	machine->index++;
	machine->state = machine->state == L_LESSAND ? L_LESSAND : L_OUT;
}

void		greater_machine(t_lexer *machine)
{
	if (ft_strchr(">&|", get_input(machine, CUR_CHAR)) != NULL)
	{
		if (get_buffer(machine, CUR_CHAR) == '>')
		{
			if (get_input(machine, CUR_CHAR) == '>')
				machine->last_lexer = E_DGREAT;
			else if (get_input(machine, CUR_CHAR) == '&')
				machine->state = L_GREATAND;
			else if (get_input(machine, CUR_CHAR) == '|')
				machine->last_lexer = E_CLOBBER;
		}
		machine->index++;
	}
	if (machine->state != L_GREATAND)
		machine->state = L_OUT;
}

void		greatand_machine(t_lexer *machine)
{
	machine->last_lexer = E_GREATAND;
	*machine->buffer->buffer = '\0';
	machine->state = L_OUT;
}

void		lessand_machine(t_lexer *machine)
{
	machine->last_lexer = E_LESSAND;
	*machine->buffer->buffer = '\0';
	machine->state = L_OUT;
}
