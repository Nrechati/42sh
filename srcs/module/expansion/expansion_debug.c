/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_debug.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 02:52:16 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/29 23:51:57 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void	print_pex_token(void *data)
{
	t_pex_token		*token;
	static char		*type[4] = {"PARAMETER", "DELIMITER", "WORD", "END"};

	token = data;
	ft_printf("type_id = [ %d ] | token_name = [ %9s] | data [ %s ]\n",
			token->type, type[token->type], token->data);
}

void		parameter_print_debug(t_list *token_list)
{
	if (token_list != NULL && (g_shell->option.option & DEBUG_OPT) != FALSE)
	{
		ft_putendl("\n\033[36m-------------- PARAMETER LEXER ---------------");
		ft_lstiter(token_list, print_pex_token);
		ft_putendl("------------------------------------\033[0m");
	}
}
