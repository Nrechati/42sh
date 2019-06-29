/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 09:49:32 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/29 16:02:23 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

static void	expand_prompt(t_sle *sle, t_vector *text)
{
	int64_t	length;
	int64_t	index;

	index = -1;
	length = vct_len(text);
	while (index < length)
	{
		length = vct_len(text);
		++index;
		if (vct_get_string(text)[index] != '\\')
			continue ;
		++index;
		if (vct_charat(text, index) == P_NAME)
			p_insert_name(text, index - 1);
		else if (vct_charat(text, index) == P_USER)
			p_insert_username(sle, text, index - 1);
		else if (vct_charat(text, index) == P_CWD)
			p_insert_cwd(sle, text, index - 1);
		else if (vct_charat(text, index) == P_HOST)
			p_insert_host(text, index - 1);
		else if (vct_charat(text, index) == P_MISS)
			p_insert_missing(sle, text, index - 1);
	}
}

void			prompt_mode(t_prompt *prompt, char *state, char *missing)
{
	prompt->state = state;
	prompt->missing_char = missing;
}

static uint8_t            prompt_need_alignment(void)
{
    int         i;
	int			pow;
    char        buff[256];
    char        ch;
    uint32_t    x;

    i = 0;
    ch = 0;
    x = 0;
	ft_bzero(buff, 256);
    write(1, "\033[6n", 4);
    while (ch != 'R')
    {
        read(0, &ch, 1);
        buff[i] = ch;
        i++;
    }
	i -= 2;
	pow = 1;
	while (buff[i] != ';')
	{
       x = x + (buff[i] - '0' ) * pow;
	   pow *= 10;
	   --i;
	}
    return ((x != 1) ? TRUE : FALSE);
}

static void		align_prompt(__unused t_sle *sle)
{
	tputs(sle->termcaps.standout_on, 1, &ft_putc);
	write(1, "%\n", 2);
	tputs(sle->termcaps.standout_off, 1, &ft_putc);
}

inline void		print_prompt(__unused t_registry *shell, t_sle *sle)
{
	t_vector	*ptext;

	if (prompt_need_alignment() == TRUE)
		align_prompt(sle);
	ptext = NULL;
	if (ft_strequ(sle->prompt.state, INT_PS1))
		ptext = vct_dup(sle->interns.ps1);
	else if (ft_strequ(sle->prompt.state, INT_PS2))
		ptext = vct_dup(sle->interns.ps2);
	else if (ft_strequ(sle->prompt.state, INT_PS3))
		ptext = vct_dup(sle->interns.ps3);

	if (ptext == NULL)
		ptext = vct_dups("[ 42sh ]-> ");
	else
		expand_prompt(sle, ptext);
	sle->prompt.text = ptext;
	print_prompt_to_window(sle, sle->prompt.text);
}
