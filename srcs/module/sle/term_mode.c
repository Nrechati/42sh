/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:13:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/11 14:36:42 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "sh21.h"
#include <termios.h>
#include <unistd.h>

static inline uint64_t alloc_otmode(t_sle *sle, struct termios *term)
{
    if ((sle->orig_mode = ft_memalloc(sizeof(struct termios)))
        == NULL)
        return (CRITICAL_ERROR);
    ft_memcpy(sle->orig_mode, term, sizeof(struct termios));
    return (SUCCESS);
}

static inline uint64_t alloc_ntmode(t_sle *sle, struct termios *term)
{
    if ((sle->term_mode = ft_memalloc(sizeof(struct termios)))
        == NULL)
        return (CRITICAL_ERROR);
    ft_memcpy(sle->term_mode, term, sizeof(struct termios));
    return (SUCCESS);
}

uint64_t    load_terminal_mode(t_sle *sle)
{
    struct termios	term;

    if ((tcgetattr(STDIN_FILENO, &term)) == FAILURE)
        return (CRITICAL_ERROR | TERMMDE_FAIL);
    if (alloc_otmode(sle, &term) != SUCCESS)
		return (CRITICAL_ERROR | TERMMDE_FAIL | MALLOC_FAIL);
    term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO | ECHOE);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
    if (alloc_ntmode(sle, &term) != SUCCESS)
		return (CRITICAL_ERROR | TERMMDE_FAIL | MALLOC_FAIL);
    return (SUCCESS);
}

int8_t			set_term_mode(t_sle *sle)
{
	if ((tcsetattr(STDIN_FILENO, TCSANOW, sle->term_mode))
					== FAILURE)
        return (FAILURE);
	return (SUCCESS);
}

int8_t			unset_term_mode(t_sle *sle)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, sle->orig_mode) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
