/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machine_interface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:28:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/17 15:59:27 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	space_lexer(t_lexer *machine)
{
	if (machine->assign_detect == ASSIGN_NEXT)
	{
		if (*machine->buffer->buffer == '\0')
		{
			vct_add(machine->buffer, ' ');
			machine->last_lexer = E_STRING;
			machine->state = L_OUT;
			machine->assign_detect = ASSIGN_ON;
		}
		else if (ft_strchr("\t ", machine->input->buffer[machine->index]))
			machine->index++;
	}
	else
	{
		machine->io_detect = 0;
		while (ft_strchr("\t ", machine->input->buffer[machine->index]))
			machine->index++;
		machine->state = L_START;
	}
}

void	start_lexer(t_lexer *machine)
{
	if (machine->input->buffer[machine->index] == '\0')
		machine->state = assign_special(machine) ? L_SPACE : L_END;
	else if (machine->input->buffer[machine->index] == ' '
			|| machine->input->buffer[machine->index] == '\t')
		machine->state = L_SPACE;
	else if (ft_strchr(SIGN_DETECT,
				machine->input->buffer[machine->index]) != NULL)
		machine->state = L_SIGN;
	else if (ft_isdigit(machine->input->buffer[machine->index]) == TRUE)
		machine->state = L_IO_NUMBER;
	else
		machine->state = L_STRING;
}

void	end_machine(t_lexer *machine)
{
	if (*machine->buffer->buffer != '\0')
		machine->state = L_OUT;
	else if (machine->last_lexer != E_END)
	{
		machine->last_lexer = E_END;
		machine->state = L_OUT;
	}
	else
		machine->state = L_FINISH;
}

void	out_lexer(t_lexer *machine)
{
	t_list	*node;
	t_token	token;

	token = generate_token(machine);
	if ((node = ft_lstnew(&token, sizeof(token))) == NULL)
		return ;
	ft_lstaddback(&machine->tokens, node);
	machine->state = L_START;
}
