/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_subprompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:41:49 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/05 10:16:18 by skuppers         ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

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
	t_vector	*line;
	char		*str;
	t_list		*new_token;

	new_token = NULL;
	while (new_token == NULL)
	{
		line = invoke_ps2prompt(g_shell, "pipe");
		str = vct_get_string(line);
		vct_del(&line);

		new_token = lexer(str);
	//	ft_strdel(&str);
	}
	ft_putchar('\n');
	free_one_node_token(&(*lst)->next);
	(*lst)->next = new_token;
}
