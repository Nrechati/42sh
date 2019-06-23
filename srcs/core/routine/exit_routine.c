/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:13:40 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/20 11:06:01 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void		free_opt(t_opt option)
{
	ft_strdel(&option.command_str);
}

static void		free_hash(t_hash hashmap, void (*del)(void *))
{
	ft_hmap_free_content(&hashmap, del);
	ft_free(hashmap.map);
	hashmap.map = NULL;
}

static void		free_registry(t_registry *shell)
{
	free_opt(shell->option);
	ft_lstdel(&shell->intern, free_node);
	free_hash(shell->hash.bin, ft_free);
	free_hash(shell->hash.blt, NULL);
}

void				shell_exit_routine(t_registry *shell, int8_t ret)
{
	if (shell != NULL)
	{
		if (shell->option.option & RECORD_HISTORY_OPT)
		{
			history(shell, NULL, WRITE_HISTFILE);
			history(shell, NULL, FREE_HISTORY);
		}
		if (shell->option.option & INTERACTIVE_OPT)
			sle(shell, NULL, SLE_EXIT);
	
		if ((shell->option.option & DEBUG_OPT) != FALSE)
			close(ft_atoi(get_var(shell->intern, INT_DBG_FD)));
		free_registry(shell);
	}
	if (shell != NULL && shell->option.option & GARBAGE_COLLECTOR_OPT)
		ft_flush_memory(PRINT);
	else
		ft_flush_memory(SILENCE);
	exit(ret);
}
