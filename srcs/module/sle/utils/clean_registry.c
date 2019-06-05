/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_registry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:14:21 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/05 10:11:19 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "sh21.h"

void	sle_teardown(t_registry *shell)
{
	(void)shell;
//	unload_autocomp();
//	unload_history();
//	unload_clipboard();

//	unload_prompt();
//	unload_cursor();
//	unload_window();

//	unload_line();

//	unload_termcaps();

/*	unset_terminal_mode(shell);
	{
	if (shell->interface.orig_mode != NULL)
		free(shell->interface.orig_mode);
	if (shell->interface.term_mode != NULL)
		free(shell->interface.term_mode);
	}


	t_history	*del;
	t_history	*ptr;

	ptr = itf->history_head;
	while (ptr != NULL)
	{
		ft_strdel(&(ptr->command));
		del = ptr->next;
		ft_free(ptr);
		ptr = del;
	}

	ft_strdel(&(itf->current_line));
	ft_strdel(&(itf->clip->buffer));
	ft_strdel(&(itf->line->buffer));
	ft_free(itf->clip);
	ft_free(itf->line);

	ft_strdel(&(itf->termcaps.clear));
	ft_strdel(&(itf->termcaps.cs_down));
	ft_strdel(&(itf->termcaps.cs_up));
	ft_strdel(&(itf->termcaps.cs_right));
	ft_strdel(&(itf->termcaps.cs_left));*/
}
