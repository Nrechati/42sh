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
