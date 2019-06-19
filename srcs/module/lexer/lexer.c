/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:23:19 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/18 16:22:20 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <stdlib.h>

char				get_buffer(t_lexer *machine, uint8_t pos)
{
	if (machine->buffer->buffer == NULL)
		return ('\0');
	if (pos & NEXT)
		return (machine->buffer->buffer[1]);
	return (machine->buffer->buffer[0]);
}

char				get_input(t_lexer *machine, uint8_t pos)
{
	if (machine->input->buffer == NULL)
		return ('\0');
	if (pos & NEXT)
		return (machine->input->buffer[machine->index + 1]);
	return (machine->input->buffer[machine->index]);
}

void				add_to_buffer(t_lexer *machine)
{
	vct_add(machine->buffer, machine->input->buffer[machine->index]);
	machine->index++;
}

static int8_t		pre_process(t_lexer *machine)
{
	if (machine->input == NULL || machine->input->buffer == NULL)
		return (FAILURE);
	while (machine->input->buffer[machine->index] == '\t'
			|| machine->input->buffer[machine->index] == ' ')
		machine->index++;
	if (machine->input->buffer[machine->index] == '\0')
		return (FAILURE);
	return (SUCCESS);
}

static void		init_machine(t_lexer *machine, t_vector *input, t_lexinfo *info)
{
	ft_bzero(machine, sizeof(t_lexer));
	machine->state = L_START;
	machine->buffer = vct_new(0);
	machine->last_lexer = E_DEFAULT;
	machine->input = input;
	machine->index = 0;
	machine->lexinfo = info;
	machine->assign_detect = ASSIGN_ON;
}

t_list			*lexer(t_vector *input)
{
	static t_lexinfo	*info = NULL;
	t_lexer				machine;

	if (info == NULL)
		info = init_lexinfo();
	init_machine(&machine, input, info);
	if (pre_process(&machine) == SUCCESS)
	{
		while (machine.state != L_FINISH)
			machine.lexinfo->lexing[machine.state](&machine);
		lexer_print_debug(g_shell, machine.tokens); // DEBUG
	}
	vct_del(&machine.buffer);
	return (machine.tokens);
}
