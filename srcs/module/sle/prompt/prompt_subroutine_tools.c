/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_subroutine.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:37:10 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/20 21:17:15 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void			subprompt_call(t_sle *sle, uint32_t option)
{
	t_vector	*new_input;

	new_input = invoke_ps2prompt(g_shell, sle, option);
	vct_ncat(sle->line, new_input, vct_len(new_input));
	vct_del(&new_input);
}

uint8_t			is_end_backslash(t_sle *sle, int index)
{
	if (vct_charat(sle->line, index) == '\\'
		&& vct_charat(sle->line, index + 1) == '\n'
		&& vct_charat(sle->line, index + 2) == '\0')
		return (TRUE);
	return (FALSE);
}

uint8_t			is_brace_exp(t_sle *sle, int index)
{
	if (vct_charat(sle->line, index) == '$'
		&& vct_charat(sle->line, index + 1) == '{')
		return (TRUE);
	return (FALSE);
}

uint8_t			is_maths_exp(t_sle *sle, int index)
{
	if (vct_charat(sle->line, index) == '$'
		&& vct_charat(sle->line, index + 1) == '('
		&& vct_charat(sle->line, index + 2) == '(')
		return (TRUE);
	return (FALSE);
}

void			backslash_process(t_sle *sle)
{
	vct_pop(sle->line);
	vct_pop(sle->line);
}
