/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:23:19 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/04 17:56:09 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <stdlib.h>

int				create_token_data(t_lexer *machine)
{
	//// ARG MAX ? 
	vct_add(machine->buffer, *machine->input->buffer);
	return (SUCCESS);
}

t_list			*lexer(t_vector *input)
{
	static t_lexinfo	*info = NULL;
	t_lexer				machine;

	if (info == NULL)
		info = init_lexinfo();
	if (input == NULL || input->buffer == NULL)
		return (NULL);
	while (*input->buffer == '\t' || *input->buffer == ' ')
		vct_del_char(input, 0);
	if (*input->buffer == '\0')
		return (NULL);
	ft_bzero(&machine, sizeof(t_lexer));
	machine.state = L_START;
	machine.buffer = vct_new(0);
	machine.last_lexer = E_DEFAULT;
	machine.input = vct_dup(input);
	machine.lexinfo = info;
	while (machine.state != L_FINISH)
		machine.lexinfo->lexing[machine.state](&machine);
	lexer_print_debug(g_shell, machine.tokens);
	vct_del(&machine.input);
	vct_del(&machine.buffer);
	return (machine.tokens);
}
