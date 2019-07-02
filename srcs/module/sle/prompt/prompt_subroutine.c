/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_subroutine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 14:58:14 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/02 19:48:07 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static uint8_t	parenthesis(t_sle *sle, t_vector *line, size_t *i)
{
	uint8_t	ret;

	(*i)++;
	ret = TRUE;
	while (vct_charat(line, *i) != ')')
	{
		if (vct_charat(line, *i) == '\0')
		{
			if (subprompt_call(sle, line, PRINT_MATHS) == FALSE)
				return (FALSE);
			continue ;
		}
		else if (is_end_backslash(line, *i) == TRUE)
			backslash_process(line);
		else if (is_brace_exp(line, *i) == TRUE)
			ret = brace_exp_routine(sle, line, i);
		else if (is_maths_exp(line, *i) == TRUE)
			ret = maths_exp_routine(sle, line, i);
		else if (vct_charat(line, *i) == '\'')
			ret = single_quote_routine(sle, line, i);
		else if (vct_charat(line, *i) == '\"')
			ret = double_quote_routine(sle, line, i);
		else if (vct_charat(line, *i) == '(')
			ret = parenthesis(sle, line, i);
		if (ret == FALSE)
			return (FALSE);
		(*i)++;
	}
	return (TRUE);
}

uint8_t			maths_exp_routine(t_sle *sle, t_vector *line, size_t *i)
{
	uint8_t	par;

	(*i) += 2;
	par = 0;
	while (par != 2)
	{
		if (parenthesis(sle, line, i) == FALSE)
			return (FALSE);
		par++;
	}
	return (TRUE);
}

uint8_t			brace_exp_routine(t_sle *sle, t_vector *line, size_t *i)
{
	uint8_t	ret;

	(*i) += 2;
	ret = TRUE;
	while (vct_charat(line, *i) != '}')
	{
		if (vct_charat(line, *i) == '\0')
		{
			if (subprompt_call(sle, line, PRINT_BRACE) == FALSE)
				return (FALSE);
			continue ;
		}
		else if (is_end_backslash(line, *i) == TRUE)
			backslash_process(line);
		else if (is_brace_exp(line, *i) == TRUE)
			ret = brace_exp_routine(sle, line, i);
		else if (is_maths_exp(line, *i) == TRUE)
			ret = maths_exp_routine(sle, line, i);
		else if (vct_charat(line, *i) == '\'')
			ret = single_quote_routine(sle, line, i);
		else if (vct_charat(line, *i) == '\"')
			ret = double_quote_routine(sle, line, i);
		if (ret == FALSE)
			return (FALSE);
		(*i)++;
	}
	return (TRUE);
}

uint8_t				verif_line(t_sle *sle, t_vector *line)
{
	size_t		i;
	uint8_t		ret;

	ret = TRUE;
	i = 0;
	while (vct_charat(line, i) != '\0')
	{
		if (is_end_backslash(line, i) == TRUE)
		{
			backslash_process(line);
			if (subprompt_call(sle, line, PRINT_NL) == FALSE)
				return (TRUE);
			continue ;
		}
		else if (is_brace_exp(line, i) == TRUE)
			ret = brace_exp_routine(sle, line, &i);
		else if (is_maths_exp(line, i) == TRUE)
			ret = maths_exp_routine(sle, line, &i);
		else if (vct_charat(line, i) == '\'')
			ret = single_quote_routine(sle, line, &i);
		else if (vct_charat(line, i) == '\"')
			ret = double_quote_routine(sle, line, &i);
		else if (vct_charat(line, i) == '\\')
			i++;
		if (ret == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
