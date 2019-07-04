/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_subprompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:41:49 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/02 19:41:19 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void			free_one_node_token(t_list **token_lst)
{
	t_token	*token;

	token = (t_token *)((*token_lst)->data);
	ft_strdel(&token->data);
	free(token);
	free(*token_lst);
	*token_lst = NULL;
}

uint8_t				need_subprompt(enum e_type state, enum e_type type)
{
	if (state == E_PIPE || state == E_DAND || state == E_OR)
	{
		if ((type == E_NEWLINE || type == E_END))
		{
			if ((g_shell->option.option & INTERACTIVE_OPT) == FALSE)
			{
				ft_printf("42sh: Unexpected EOF while looking for matching "
						"%s\n", (char *)g_shell->grammar[state]);
				add_var(&g_shell->intern, "?", "1", READONLY_VAR);
				return (FALSE);
			}
			return (TRUE);
		}
	}
	ft_dprintf(2, "42sh: syntax error near unexpected token `%s'\n",
				type == E_NEWLINE ? "\\n" : g_shell->grammar[type]);
	return (FALSE);
}

static uint64_t		set_option_subprompt(enum e_type state)
{
	uint64_t	option;

	option = SLE_PS2_PROMPT;
	if (state == E_PIPE)
		option |= PRINT_PIPE;
	else if (state == E_DAND)
		option |= PRINT_AND;
	else if (state == E_OR)
		option |= PRINT_OR;
	return (option);
}

uint8_t				parser_subprompt(enum e_type state,
						t_vector *input, t_list **lst)
{
	t_vector	*line;
	t_list		*new_token;
	uint64_t	option;

	new_token = NULL;
	line = NULL;
	option = set_option_subprompt(state);
	sle(g_shell, &line, option);
//	history(g_shell, vct_get_string(input), ADD_ENTRY);
	if (line == NULL)// || do_history_exp(&line) == FAILURE)
	{
//		history(g_shell, NULL, POP_ENTRY);
		return (FALSE);
	}
//	history(g_shell, NULL, POP_ENTRY);
	if (line->buffer == NULL || ft_strequ(line->buffer, "\n") == TRUE)
		return (parser_subprompt(state, input, lst));
	vct_pop(input);
	vct_add(input, ' ');
	new_token = lexer(line, SHELL);
	vct_ncat(input, line, vct_len(line));
	vct_del(&line);
	free_one_node_token(&(*lst)->next);
	(*lst)->next = new_token;
	return (TRUE);
}
