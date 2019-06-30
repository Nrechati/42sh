/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_subroutine.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:37:10 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/29 18:46:23 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

uint8_t		subprompt_call(t_sle *sle, t_vector *line, uint32_t option)
{
	t_vector	*new_input;
	static const char	*prompt_type[] = {PROMPT_PIPE, PROMPT_QUOTE,
										PROMPT_DQUOTE, PROMPT_BQUOTE,
										PROMPT_NL, PROMPT_AND, PROMPT_OR,
										PROMPT_BRACE, PROMPT_MATHS};

	if (is_shell_interactive(g_shell) == FALSE)
	{
		ft_printf("42sh: Unexpected EOF while looking for matching %s.\n",
						(char *)prompt_type[option]);
		return (FALSE);
	}
	new_input = invoke_ps2prompt(g_shell, sle, option);
	if (new_input == NULL)
	{
		vct_del(&new_input);
		return (FALSE);
	}
	vct_ncat(line, new_input, vct_len(new_input));
	vct_del(&new_input);
	return (TRUE);
}

uint8_t			is_end_backslash(t_vector *line, int index)
{
	if (vct_charat(line, index) == '\\'
		&& vct_charat(line, index + 1) == '\n'
		&& vct_charat(line, index + 2) == '\0')
		return (TRUE);
	return (FALSE);
}

uint8_t			is_brace_exp(t_vector *line, int index)
{
	if (vct_charat(line, index) == '$'
		&& vct_charat(line, index + 1) == '{')
		return (TRUE);
	return (FALSE);
}

uint8_t			is_maths_exp(t_vector *line, int index)
{
	if (vct_charat(line, index) == '$'
		&& vct_charat(line, index + 1) == '('
		&& vct_charat(line, index + 2) == '(')
		return (TRUE);
	return (FALSE);
}

void			backslash_process(t_vector *line)
{
	vct_pop(line);
	vct_pop(line);
}
