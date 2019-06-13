/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:18:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/13 17:43:37 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

static t_resolution	init_resolve(t_registry *shell, t_list *tokens)
{
	t_resolution	resolve;

	shell->analyzer_signal = FALSE;
	ft_bzero(&resolve, sizeof(t_resolution));
	resolve.tokens = tokens;
	resolve.token.type = E_DEFAULT;
	return (resolve);
}

int8_t				execution_pipeline(t_registry *shell, t_vector *input)
{
	t_list			*command_group;
	t_resolution	resolve;
	t_list			*tokens;

	tokens = lexer(input);
	resolve = init_resolve(shell, tokens);
	while (resolve.tokens)
	{
		command_group = NULL;
		if (parser(resolve.tokens) == FAILURE)
		{
			ft_lstdel(&resolve.tokens, del_token);
			return (FAILURE);
		}

		command_group = analyzer(&resolve);
		if (command_group)
			interpreter(shell, &command_group);
		lexer_print_debug(shell, resolve.tokens);
	}
	return (SUCCESS);
}
