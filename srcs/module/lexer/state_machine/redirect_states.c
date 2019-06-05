/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_states.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:23:05 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/04 17:56:34 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	lesser_machine(t_lexer *machine)
{
	uint32_t	checker;

	checker = 0;
	if (machine->last_lexer == E_DLESS
			&& *machine->input->buffer == '-' && ++checker)
		machine->last_lexer = E_DLESSDASH;
	else if (*machine->buffer->buffer == '<' && *machine->input->buffer == '<')
	{
		if (machine->last_lexer != E_DLESS)
		{
			machine->last_lexer = E_DLESS;
			if (create_token_data(machine) != FAILURE)
				vct_del_char(machine->input, 0);
			return ;
		}
	}
	else if (*machine->input->buffer == '>' || *machine->input->buffer == '&')
	{
		if (*machine->buffer->buffer == '<'
				&& *machine->input->buffer == '&' && ++checker)
			machine->state = L_LESSAND;
		else if (*machine->buffer->buffer == '<'
				&& *machine->input->buffer == '>' && ++checker)
			machine->last_lexer = E_LESSGREAT;
	}
	if (checker != FALSE)
		vct_del_char(machine->input, 0);
	machine->state = machine->state == L_LESSAND ? L_LESSAND : L_OUT;
}

void	greater_machine(t_lexer *machine)
{
	uint32_t	checker;

	checker = 0;
	if (ft_strchr(">&|", *machine->input->buffer) != NULL)
	{
		if (*machine->buffer->buffer == '>'
				&& *machine->input->buffer == '>' && ++checker)
			machine->last_lexer = E_DGREAT;
		else if (*machine->buffer->buffer == '>'
				&& *machine->input->buffer == '&' && ++checker)
			machine->state = L_GREATAND;
		else if (*machine->buffer->buffer == '>'
				&& *machine->input->buffer == '|' && ++checker)
			machine->last_lexer = E_CLOBBER;
	}
	if (checker != FALSE)
		vct_del_char(machine->input, 0);
	machine->state = machine->state == L_GREATAND ? L_GREATAND : L_OUT;
}

void	greatand_machine(t_lexer *machine)
{
	machine->last_lexer = E_GREATAND;
	*machine->buffer->buffer = '\0';
	machine->state = L_OUT;
}

void	lessand_machine(t_lexer *machine)
{
	machine->last_lexer = E_LESSAND;
	*machine->buffer->buffer = '\0';
	machine->state = L_OUT;
}
