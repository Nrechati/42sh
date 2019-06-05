/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:18:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/04 19:12:54 by skuppers         ###   ########.fr       */
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
	resolve.token_list = token_list;
	resolve.token.type = E_DEFAULT;
	return (resolve);
}

int8_t				execution_pipeline(t_registry *shell, t_vector *input)
{
	t_resolution	resolve;
	t_list			*token_list;

	token_list = lexer(input);
	resolve = init_resolve(shell, token_list);
	while (resolve.token_list)
	{
		if (parser(resolve.token_list) == FAILURE)
		{
			ft_lstdel(&resolve.token_list, del_token);
			return (FAILURE);
		}
		shell->current_job = analyzer(&resolve);
		lexer_print_debug(shell, resolve.token_list);
		if (resolve.valid == 1)
			launch_job(shell, resolve.job_list);
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
