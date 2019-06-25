/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:18:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/24 16:15:01 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>


static t_resolution	init_resolve(t_list *tokens)
{
	t_resolution	resolve;

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

	tokens = lexer(input, MATHS);
	exit(FAILURE);
	resolve = init_resolve(tokens);
	while (resolve.tokens)
	{
		command_group = NULL;
		if (parser(input, resolve.tokens) == FAILURE)
		{
			history(shell, ft_strdup(vct_get_string(input)), ADD_ENTRY);
			ft_lstdel(&resolve.tokens, del_token);
			return (FAILURE);
		}
		command_group = analyzer(&resolve);
		if (command_group)
		{
			history(shell, ft_strdup(vct_get_string(input)), ADD_ENTRY);
			interpreter(shell, &command_group, 0);
			load_signal_profile(DFLT_PROFILE);
		}
		lexer_print_debug(shell, resolve.tokens);
	}
	return (SUCCESS);
}
