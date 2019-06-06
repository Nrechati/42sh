/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:18:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/06 12:51:37 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

static t_resolution	init_resolve(t_registry *shell, t_list *token_list)
{
	t_resolution	resolve;

	shell->analyzer_signal = FALSE;
	define_analyzer_signals();
	ft_bzero(&resolve, sizeof(t_resolution));
	resolve.tokens = token_list;
	resolve.token.type = E_DEFAULT;
	return (resolve);
}

int8_t				execution_pipeline(t_registry *shell, t_list *token_list)
{
	t_resolution	resolve;

	resolve = init_resolve(shell, token_list);
	while (resolve.tokens)
	{
		if (parser(resolve.tokens) == FAILURE)
		{
			ft_lstdel(&resolve.tokens, del_token);
			return (FAILURE);
		}
		shell->current_job = analyzer(&resolve);
		lexer_print_debug(shell, resolve.tokens);
		if (resolve.valid == 1)
			launch_job(shell, resolve.tokens);
	}
	define_ign_signals();
	return (SUCCESS);
}

void				shell_exit_routine(t_registry *shell)
{
	if ((shell->option.option & DEBUG_OPT) != FALSE)
		close(ft_atoi(get_var(shell->intern, INT_DBG_FD)));
	free_registry(shell);
}
