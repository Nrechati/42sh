/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:36:14 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/08 11:03:35 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termios.h>
#include <termcap.h>

uint64_t    get_terminal_info(t_registry *shell)
{
    char    *terminal;

    terminal = NULL;
    terminal = getenv("TERM");
    if (terminal == NULL || ft_strequ(terminal, ""))
    {
        terminal = INT_TERM_DFLT_VALUE;
		add_var(&shell->intern, INT_TERM, INT_TERM_DFLT_VALUE, SET_VAR);
    }
    else
        add_var(&shell->intern, INT_TERM, terminal, SET_VAR);
    if (tgetent(NULL, terminal) == FAILURE)
        return (CRITICAL_ERROR | INVALID_TERM);
    return (SUCCESS);
}

//add more error handling around the dup TGETSTR_FAIL
uint64_t    init_termcaps(t_termcaps *termcap)
{
    termcap->standout_on = ft_strdup(tgetstr("so", NULL));
    termcap->standout_off = ft_strdup(tgetstr("se", NULL));
    termcap->clear = ft_strdup(tgetstr("cl", NULL));
    termcap->up = ft_strdup(tgetstr("up", NULL));
    termcap->down = ft_strdup(tgetstr("do", NULL));
    termcap->left = ft_strdup(tgetstr("le", NULL));
    termcap->right = ft_strdup(tgetstr("nd", NULL));
    return (SUCCESS);
}
