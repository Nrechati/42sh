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

static void	lesser_addition(t_lexer *machine)
{
	if (*machine->buffer->buffer == '<'
			&& machine->input->buffer[machine->index] == '&')
		machine->state = L_LESSAND;
	else if (*machine->buffer->buffer == '<'
			&& machine->input->buffer[machine->index] == '>')
		machine->last_lexer = E_LESSGREAT;
	else
		return ;
	machine->index++;

}

void		lesser_machine(t_lexer *machine)
{
	if (machine->last_lexer == E_DLESS
			&& machine->input->buffer[machine->index] == '-')
	{
		machine->last_lexer = E_DLESSDASH;
		machine->index++;
	}
	else if (*machine->buffer->buffer == '<'
			&& machine->input->buffer[machine->index] == '<'
			&& machine->input->buffer[machine->index + 1] != '&'
			&& (machine->last_lexer != E_DLESS))
	{
		machine->last_lexer = E_DLESS;
		vct_add(machine->buffer, machine->input->buffer[machine->index]);
		machine->index++;
		return ;
	}
	else if (machine->input->buffer[machine->index] == '>'
			|| machine->input->buffer[machine->index] == '&')
		lesser_addition(machine);
	machine->state = machine->state == L_LESSAND ? L_LESSAND : L_OUT;
}

void		greater_machine(t_lexer *machine)
{
	if (ft_strchr(">&|", machine->input->buffer[machine->index]) != NULL)
	{
		if (*machine->buffer->buffer == '>'
				&& machine->input->buffer[machine->index] == '>')
			machine->last_lexer = E_DGREAT;
		else if (*machine->buffer->buffer == '>'
				&& machine->input->buffer[machine->index] == '&')
			machine->state = L_GREATAND;
		else if (*machine->buffer->buffer == '>'
				&& machine->input->buffer[machine->index] == '|')
			machine->last_lexer = E_CLOBBER;
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
