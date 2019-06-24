/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:42:01 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/24 16:10:45 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void	generate_maths_grammar(void)
{
	static const char	*grammar[NB_OF_MTOKENS] = {M_TIMES, M_DIVIDE, M_MODULO,
										M_PLUS, M_MINUS, M_OPENP, M_CLOSEP,
										M_LESS, M_GREAT,
										M_LESSOR, M_GREATOR, M_EQUAL, M_NEQUAL,
										M_AND, M_OR, M_ASSIGN, M_STRING,
										M_NB_DEC, M_NB_OCT, M_NB_HEX, M_END,
										M_START};

	g_shell->grammar_m = grammar;
}

static void	generate_shell_grammar(void)
{
	static const char	*grammar[NB_OF_TOKENS] = { N_DB_QUOTE, N_PIPE,
			N_PARENT_OPEN, N_PARENT_CLOSE, N_GREAT, N_LESS, N_SEMICOLON,
			N_BACKQUOTE, N_AND, N_HOOK_OPEN, N_HOOK_CLOSE, N_BRACKET_OPEN,
			N_BRACKET_CLOSE, N_HASH, N_PERCENT, N_NEWLINE, N_DAND, N_OR,
			N_DSEMI, N_DLESS, N_DGREAT, N_LESSAND, N_GREATAND, N_LESSGREAT,
			N_ANDDGREAT, N_ANDGREAT, N_DLESSDASH, N_CLOBBER, N_DEQ,
			N_NOTEQ, N_CASE, N_DO, N_DONE, N_ELIF, N_ELSE, N_ESAC, N_FI, N_FOR,
			N_IF, N_IN, N_THEN, N_UNTIL, N_WHILE, N_IO_NUMBER, N_ASSIGN,
			N_STRING, N_SPSTRING, N_END, N_ERROR, N_START};

	g_shell->grammar = grammar;
}

void		generate_grammar(void)
{
	generate_shell_grammar();
	generate_maths_grammar();
}
