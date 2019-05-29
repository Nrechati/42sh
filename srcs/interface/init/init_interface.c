/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 14:47:53 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/27 11:33:20 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "interface_functions.h"
#include <termios.h>
#include <termcap.h>
#include "log.h"

uint64_t    get_terminal_info(t_registry *shell)
{
    char    *terminal;

    terminal = NULL;
    terminal = getenv("TERM");
    if (terminal == NULL || ft_strequ(terminal, ""))
    {
        terminal = INT_TERM_DFLT_VALUE;
		add_internal(shell, INT_TERM, INT_TERM_DFLT_VALUE);
    }
    else
        add_internal(shell, INT_TERM, terminal);
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
	if (termcap->up == NULL || termcap->down == NULL)
		log_print(g_shell, LOG_INFO, "problem.\n");
    return (SUCCESS);
}
