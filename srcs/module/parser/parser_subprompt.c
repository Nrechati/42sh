/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_subprompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:41:49 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:52:29 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_registry	*g_shell;

static void			free_one_node_token(t_list **token_lst)
{
	t_token	*token;

	token = (t_token *)((*token_lst)->data);
	ft_strdel(&token->data);
	ft_free(token);
	ft_free(*token_lst);
	*token_lst = NULL;
}

uint8_t				need_subprompt(enum e_type state, enum e_type type)
{
	if (state == E_PIPE && type == E_END
			&& (g_shell->option.option & INTERACTIVE_OPT))
		return (TRUE);
	return (FALSE);
}

void				parser_subprompt(t_list **lst)
{
	t_list		*new_token;
	char		*line;

	line = NULL;
	new_token = NULL;
	while (new_token == NULL)
	{
		invoke_sub_prompt(g_shell, &line, "pipe> ");
		g_shell->interface.state = INT_PS1;
		new_token = lexer(line);
		ft_strdel(&line);
	}
	ft_putchar('\n');
	free_one_node_token(&(*lst)->next);
	(*lst)->next = new_token;
}
