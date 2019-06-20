/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:23:19 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/20 11:18:24 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <stdlib.h>
/*
uint8_t				is_braceparam(t_lexer * lexer)
{
}*/

uint8_t				is_end_of_cmd(t_lexer *machine)
{
	if (get_input(machine, CUR_CHAR) == '\n'
		&& get_input(machine, NEXT_CHAR) == '\0')
		return (TRUE);
	return (FALSE);
}

void				subprompt_calling(t_lexer *machine, uint64_t option)
{
	t_vector	*new_input;
	uint64_t	opt_nl;

	opt_nl = SLE_PS2_PROMPT | PRINT_NL;
	if (opt_nl != option || is_end_of_cmd(machine) == FALSE)
	{
		new_input = vct_new(0);
		while (new_input->buffer[0] == '\0')
			sle(g_shell, &new_input, option);
		vct_ncat(machine->input, new_input, vct_len(new_input));
		vct_del(&new_input);
	}
}

char				get_buffer(t_lexer *machine, uint8_t pos)
{
	if (machine->buffer->buffer == NULL)
		return ('\0');
	if (pos & NEXT_CHAR)
		return (machine->buffer->buffer[1]);
	else if (pos & NEXT_NEXT_CHAR)
		return (machine->buffer->buffer[2]);
	return (machine->buffer->buffer[0]);
}

char				get_input(t_lexer *machine, uint8_t pos)
{
	if (machine->input->buffer == NULL)
		return ('\0');
	if (pos & NEXT_CHAR)
		return (machine->input->buffer[machine->index + 1]);
	else if (pos & NEXT_NEXT_CHAR)
		return (machine->input->buffer[machine->index + 2]);
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
