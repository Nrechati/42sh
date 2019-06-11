/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machine_interface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:28:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/04 17:56:48 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	start_lexer(t_lexer *machine)
{
	if (*machine->input->buffer == '\0')
		machine->state = L_END;
	else if (*machine->input->buffer == ' ' || *machine->input->buffer == '\t')
	{
		machine->io_detect = 0;
		while (*machine->input->buffer == ' '
				|| *machine->input->buffer == '\t')
			vct_cut(machine->input);
	}
	else if (ft_strchr(SIGN_DETECT, *machine->input->buffer) != NULL)
		machine->state = L_SIGN;
	else if (ft_isdigit(*machine->input->buffer) == TRUE)
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
