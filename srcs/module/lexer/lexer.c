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

char				get_input(t_lexer *lexer, uint8_t pos)
{
	if (lexer->input->buffer == NULL)
		return ('\0');
	if (pos & NEXT_CHAR)
		return (lexer->input->buffer[lexer->index + 1]);
	else if (pos & NEXT_NEXT_CHAR)
		return (lexer->input->buffer[lexer->index + 2]);
	return (lexer->input->buffer[lexer->index]);
}

void				add_to_buffer(t_lexer *lexer)
{
	vct_add(lexer->buffer, lexer->input->buffer[lexer->index]);
	lexer->index++;
}

static void		init_lexer(t_lexer *lexer, t_vector *input)
{
	ft_bzero(lexer, sizeof(t_lexer));
	lexer->buffer = vct_new(0);
	lexer->input = input;
	lexer->index = 0;
	lexer->state = L_PROCESS;
	lexer->token_type = E_DEFAULT;
	lexer->inhibitor = NO_FLAG;
	lexer->assignation = POSSIBLE;
}

t_list			*lexer(t_vector *input)
{
	t_lexer	lexer;

	init_lexer(&lexer, input);
	while (lexer.state != L_FINISH)
		lexer.state == L_OUT ? out_lexer(&lexer) : process_lexer(&lexer);
	lexer_print_debug(g_shell, lexer.tokens);
	vct_del(&lexer.buffer);
	return (lexer.tokens);
}
