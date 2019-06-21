/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:13:18 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/04 17:57:10 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		print_token(void *data)
{
	t_token *token;

	token = data;
	ft_printf("type_id = [ %2d ] | type_name = [ %5s ] | data = [ %s ]\n",
				token->type, token->type == E_NEWLINE ? "\\n"
				: g_grammar[token->type], token->data);
}

void		lexer_print_debug(t_registry *shell, t_list *token_list)
{
	if (token_list != NULL && (shell->option.option & DEBUG_OPT) != FALSE)
	{
		ft_putendl("\n\033[36m-------------- LEXER ---------------");
		ft_lstiter(token_list, print_token);
		ft_putendl("------------------------------------\033[0m");
	}
}
