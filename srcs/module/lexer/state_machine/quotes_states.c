/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 13:34:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/20 18:25:22 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static uint8_t	is_closed(t_lexer *machine, char close)
{
	if (get_input(machine, CUR_CHAR) == close)
		return (TRUE);
	else if ((g_shell->option.option & INTERACTIVE_OPT) == FALSE)
	{
		if (get_input(machine, CUR_CHAR) == '\0')
			return (TRUE);
	}
	return (FALSE);
}

void	single_quote_machine(t_lexer *machine)
{
	while (is_closed(machine, '\'') == FALSE)
			add_to_buffer(machine);
	if (get_input(machine, CUR_CHAR) != '\0')
		add_to_buffer(machine);
	machine->state = L_STRING;
}

void	double_quote_machine(t_lexer *machine)
{
	while (is_closed(machine, '\"') == FALSE)
	{
		if (get_input(machine, CUR_CHAR) == '\0')
			subprompt_calling(machine, SLE_PS2_PROMPT | PRINT_DQUOTE);
		else if (get_input(machine, CUR_CHAR) == '\\')
		{
			machine->index++;
			if (get_input(machine, CUR_CHAR) != '\"')
				add_to_buffer(machine);
		}
		else
			add_to_buffer(machine);
	}
	add_to_buffer(machine);
	if (get_input(machine, CUR_CHAR) != '\"')
		machine->state = L_STRING;
}
