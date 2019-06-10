/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:18:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/10 20:45:59 by cempassi         ###   ########.fr       */
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

int8_t				execution_pipeline(t_registry *shell, t_list *tokens)
{
	t_list			*cmd_group;
	t_resolution	resolve;

	resolve = init_resolve(shell, tokens);
	while (resolve.tokens)
	{
		if (parser(resolve.tokens) == FAILURE)
		{
			ft_lstdel(&resolve.tokens, del_token);
			return (FAILURE);
		}
		cmd_group = analyzer(&resolve);
		interpreter(shell, &cmd_group);
		lexer_print_debug(shell, resolve.tokens);
	}
	return (SUCCESS);
}

void				shell_exit_routine(t_registry *shell)
{
	if ((shell->option.option & DEBUG_OPT) != FALSE)
		close(ft_atoi(get_var(shell->intern, INT_DBG_FD)));
	free_registry(shell);
}
