/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_subroutine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 14:58:14 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/24 19:12:39 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void	parenthesis(t_sle *sle, size_t *i)
{
	uint8_t	par;

	par = FALSE;
	while (par == FALSE)
	{
		if (vct_charat(sle->line, *i) == '\0')
			subprompt_call(sle, PRINT_MATHS);
		else if (vct_charat(sle->line, *i) == ')')
		{
			(*i)++;
			par = TRUE;
		}
		else if (vct_charat(sle->line, *i) == '(')
		{
			(*i)++;
			parenthesis(sle, i);
		}
		else
			(*i)++;
	}
}

void	maths_exp_routine(t_sle *sle, size_t *i)
{
	(*i) += 3;
	parenthesis(sle, i);
	parenthesis(sle, i);
}

void	brace_exp_routine(t_sle *sle, size_t *i)
{
	(*i) += 2;
	while (vct_charat(sle->line, *i) != '}')
	{
		if (vct_charat(sle->line, *i) == '\0')
		{
			subprompt_call(sle, PRINT_BRACE);
			continue ;
		}
		else if (is_end_backslash(sle, *i) == TRUE)
			backslash_process(sle);
		else if (vct_charat(sle->line, *i) == '\"')
			double_quote_routine(sle, i);
		(*i)++;
	}
}

void	single_quote_routine(t_sle *sle, size_t *i)
{
	(*i)++;
	while (vct_charat(sle->line, *i) != '\'')
	{
		if (vct_charat(sle->line, *i) == '\0')
			subprompt_call(sle, PRINT_QUOTE);
		else
			(*i)++;
	}
}

void	double_quote_routine(t_sle *sle, size_t *i)
{
	(*i)++;
	while (vct_charat(sle->line, *i) != '\"')
	{
		if (vct_charat(sle->line, *i) == '\0')
		{
			subprompt_call(sle, PRINT_DQUOTE);
			continue ;
		}
		else if (is_brace_exp(sle, *i) == TRUE)
			brace_exp_routine(sle, i);
		else if (is_maths_exp(sle, *i) == TRUE)
			maths_exp_routine(sle, i);
		else if (vct_charat(sle->line, *i) == '\\')
			(*i)++;
		(*i)++;
	}
}

void				verif_line(t_sle *sle)
{
	size_t		i;

	i = 0;
	while (vct_charat(sle->line, i) != '\0')
	{
		if (is_end_backslash(sle, i) == TRUE)
		{
			backslash_process(sle);
			subprompt_call(sle, PRINT_NL);
			continue ;
		}
		else if (is_brace_exp(sle, i) == TRUE)
			brace_exp_routine(sle, &i);
		else if (is_maths_exp(sle, i) == TRUE)
			maths_exp_routine(sle, &i);
		else if (vct_charat(sle->line, i) == '\'')
			single_quote_routine(sle, &i);
		else if (vct_charat(sle->line, i) == '\"')
			double_quote_routine(sle, &i);
		else if (vct_charat(sle->line, i) == '\\')
			i++;
		i++;
	}
}
