/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_registry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:14:21 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/06 14:35:20 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "sh21.h"

static void	sle_destroy(__unused t_sle *sle)
{
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

	ptr = sle->history_head;
	while (ptr != NULL)
	{
		ft_strdel(&(ptr->command));
		del = ptr->next;
		ft_free(ptr);
		ptr = del;
	}

	ft_strdel(&(sle->current_line));
	ft_strdel(&(sle->clip->buffer));
	ft_strdel(&(sle->line->buffer));
	ft_free(sle->clip);
	ft_free(sle->line);

	ft_strdel(&(sle->termcaps.clear));
	ft_strdel(&(sle->termcaps.cs_down));
	ft_strdel(&(sle->termcaps.cs_up));
	ft_strdel(&(sle->termcaps.cs_right));
	ft_strdel(&(sle->termcaps.cs_left));*/
}

void	sle_teardown(t_sle *sle)
{
	sle_destroy(sle);
}
