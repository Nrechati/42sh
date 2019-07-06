/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_subroutine_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:48:14 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/06 17:03:37 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

uint8_t			single_quote_routine(t_vector *line, size_t *i)
{
	(*i)++;
	while (vct_charat(line, *i) != '\'')
	{
		if (vct_charat(line, *i) == '\0')
		{
			if (subprompt_call(line, PRINT_QUOTE) == FALSE)
				return (FALSE);
			continue ;
		}
		(*i)++;
	}
	return (TRUE);
}

uint8_t			double_quote_routine(t_vector *line, size_t *i)
{
	uint8_t	ret;

	(*i)++;
	ret = TRUE;
	while (vct_charat(line, *i) != '\"')
	{
		if (vct_charat(line, *i) == '\0')
		{
			if (subprompt_call(line, PRINT_DQUOTE) == FALSE)
				return (FALSE);
			continue ;
		}
		else if (vct_charat(line, *i) == '\\')
			(*i)++;
		else if (is_brace_exp(line, *i) == TRUE)
			ret = brace_exp_routine(line, i);
		else if (is_maths_exp(line, *i) == TRUE)
			ret = maths_exp_routine(line, i);
		if (ret == FALSE)
			return (FALSE);
		(*i)++;
	}
	return (TRUE);
}

uint8_t			brace_routine(t_vector *line, size_t *i)
{
	(*i)++;
	while (vct_charat(line, *i) != '}')
	{
		if (vct_charat(line, *i) == '\0')
		{
			if (subprompt_call(line, PRINT_BRACE) == FALSE)
				return (FALSE);
			continue ;
		}
		(*i)++;
	}
	return (TRUE);
}

uint8_t			backquote_routine(t_vector *line, size_t *i)
{
	(*i)++;
	while (vct_charat(line, *i) != '`')
	{
		if (vct_charat(line, *i) == '\0')
		{
			if (subprompt_call(line, PRINT_BQUOTE) == FALSE)
				return (FALSE);
			continue ;
		}
		(*i)++;
	}
	return (TRUE);
}

uint8_t			brackets_routine(t_vector *line, size_t *i)
{
	(*i)++;
	while (vct_charat(line, *i) != ']')
	{
		if (vct_charat(line, *i) == '\0')
		{
			if (subprompt_call(line, PRINT_BRACKET) == FALSE)
				return (FALSE);
			continue ;
		}
		(*i)++;
	}
	return (TRUE);
}

uint8_t			parenthese_routine(t_vector *line, size_t *i)
{
	(*i)++;
	while (vct_charat(line, *i) != ')')
	{
		if (vct_charat(line, *i) == '\0')
		{
			if (subprompt_call(line, PRINT_PARENTHESE) == FALSE)
				return (FALSE);
			continue ;
		}
		(*i)++;
	}
	return (TRUE);
}
