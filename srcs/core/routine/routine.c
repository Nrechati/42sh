/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:18:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/29 18:53:22 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

void		init_process(t_process *process)
{
	ft_bzero(process, sizeof(t_process));
}

int8_t		init_shell(t_registry *shell)
{
	g_shell = shell; // OK ?
	shell->analyzer_signal = FALSE;
	init_debug_logger(shell);
	print_opt(shell);
	return (SUCCESS);
}

void		reset_analyzer(t_registry *shell, t_resolution *resolve)
{
	ft_stckinit(&resolve->stack);
	resolve->state = P_START;
	resolve->env = shell->intern;
	resolve->oflags = 0;
	resolve->valid = 0;
	init_process(&resolve->process);
	ft_bzero(&resolve->job, sizeof(t_job));
}

int8_t		execution_pipeline(t_registry *shell, t_list *token_list)
{
	t_resolution	resolve;

	shell->analyzer_signal = FALSE;
	define_analyzer_signals();
	ft_bzero(&resolve, sizeof(t_resolution));
	resolve.token_list = token_list;
	resolve.token.type = E_DEFAULT;
	lexer_print_debug(shell, resolve.token_list);
	while (resolve.token_list)
	{
		if (parser(resolve.token_list) == FAILURE)
		{
			ft_lstdel(&resolve.token_list, del_token);
			return (FAILURE);
		}
		reset_analyzer(shell, &resolve);
		shell->current_job = analyzer(&resolve);
		analyzer_print_debug(shell, &resolve);
		lexer_print_debug(shell, resolve.token_list);
		if (resolve.valid == 1)
			launch_job(shell, resolve.job_list);
		delete_analyzer(&resolve);
	}
	define_ign_signals();
	return (SUCCESS);
}

void		shell_exit_routine(t_registry *shell)
{
	if ((shell->option.option & DEBUG_OPT) != FALSE)
		close(ft_atoi(get_intern_var(shell, INT_DBG_FD)));
	free_registry(shell);
}
