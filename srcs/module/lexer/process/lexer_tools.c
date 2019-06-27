/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 20:28:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/24 15:34:00 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		init_lexer(t_lexer *lexer, t_vector *input)
{
	ft_bzero(lexer, sizeof(t_lexer));
	lexer->buffer = vct_new(0);
	lexer->input = input;
	lexer->index = 0;
	lexer->state = L_PROCESS;
	lexer->token_type = E_DEFAULT;
	lexer->last_token_mtype = E_M_DEFAULT;
	lexer->token_mtype = E_M_DEFAULT;
	lexer->inhibitor = NO_FLAG;
	lexer->assignation = POSSIBLE;
	lexer->parenthesis = 0;
}

char	get_input(t_lexer *lexer, uint8_t pos)
{
	if (pos & NEXT_CHAR)
		return (vct_charat(lexer->input, lexer->index + 1));
	else if (pos & NEXT_NEXT_CHAR)
		return (vct_charat(lexer->input, lexer->index + 2));
	return (vct_charat(lexer->input, lexer->index));
}

void	add_to_buffer(t_lexer *lexer)
{
	vct_add(lexer->buffer, lexer->input->buffer[lexer->index]);
	lexer->index++;
}
