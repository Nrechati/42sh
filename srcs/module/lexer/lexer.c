/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:23:19 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/06 19:13:13 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <stdlib.h>

static int8_t		pre_process(t_lexer *machine)
{
	if (machine->input == NULL || machine->input->buffer == NULL)
		return (FAILURE);
	while (*machine->input->buffer == '\t' || *machine->input->buffer == ' ')
		vct_cut(machine->input);
	if (*machine->input->buffer == '\0')
		return (FAILURE);
	return (SUCCESS);
}

static void		init_machine(t_lexer *machine, t_vector *input, t_lexinfo *info)
{
	ft_bzero(machine, sizeof(t_lexer));
	machine->state = L_START;
	machine->buffer = vct_new(0);
	machine->last_lexer = E_DEFAULT;
	machine->input = vct_dup(input);
	machine->lexinfo = info;
}

static void		free_machine_vct(t_lexer *machine)
{
	vct_del(&machine->input);
	vct_del(&machine->buffer);
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
	free_machine_vct(&machine);
	return (machine.tokens);
}
