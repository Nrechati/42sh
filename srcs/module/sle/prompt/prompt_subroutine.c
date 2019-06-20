/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_subroutine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 14:58:14 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/20 18:32:19 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void			subprompt_call(t_registry *shell, t_sle *sle, uint64_t option)
{
	t_vector	*new_input;

	new_input = invoke_ps2prompt(shell, sle, option);
	vct_ncat(sle->line, new_input, vct_len(new_input));
	vct_del(&new_input);
}

static uint8_t is_end_backslash(t_sle *sle, int index)
{
	if (vct_charat(sle->line, index) == '\\'
		&& vct_charat(sle->line, index + 1) == '\n'
		&& vct_charat(sle->line, index + 2) == '\0')
		return (TRUE);
	return (FALSE);
}

static uint8_t is_brace_exp(t_sle *sle, int index)
{
	if (vct_charat(sle->line, index) == '$'
		&& vct_charat(sle->line, index + 1) == '{')
		return (TRUE);
	return (FALSE);
}

static uint8_t is_maths_exp(t_sle *sle, int index)
{
	if (vct_charat(sle->line, index) == '$'
		&& vct_charat(sle->line, index + 1) == '('
		&& vct_charat(sle->line, index + 2) == '(')
		return (TRUE);
	return (FALSE);
}

static uint64_t backslash_process(t_sle *sle, uint16_t *next_close)
{
	vct_pop(sle->line);
	vct_pop(sle->line);
	*next_close = ANY;
	return (PRINT_NL);
}

static uint64_t single_quote_process(uint16_t *next_close, size_t *index)
{
	(void)index;
	*next_close = SP_SINGLE_QUOTE;
	return (PRINT_QUOTE);
}

static uint64_t double_quote_process(uint16_t *next_close, size_t *index)
{
	(void)index;
	*next_close = SP_DOUBLE_QUOTE;
	return (PRINT_DQUOTE);
}

static uint64_t brace_exp_process(uint16_t *next_close, size_t *index)
{
	(void)index;
	*next_close = SP_BRACE_EXP;
	return (PRINT_BRACE);
}

static uint64_t maths_exp_process(uint16_t *next_close, size_t *index)
{
	(void)index;
	*next_close = SP_MATHS_EXP;
	return (PRINT_MATHS);
}

static uint64_t	maths_exp_routine(t_sle *sle, size_t *i, uint16_t *next_close)
{
	if (vct_charat(sle->line, *i) == '\0')
	{
		vct_pop(sle->line);
		vct_pop(sle->line);
		if (*i > 1)
			(*i) -= 2;
	}
	if (vct_charat(sle->line, *i) == '\0')
		return (maths_exp_process(next_close, i));
	else if (vct_charat(sle->line, *i) == ')'
			&& vct_charat(sle->line, *i + 1) == ')')
	{
		(*i)++;
		*next_close = IS_CLOSE;
	}
	return (0);
}

static uint64_t	brace_exp_routine(t_sle *sle, size_t *i, uint16_t *next_close)
{
	if (is_end_backslash(sle, *i) == TRUE)
		backslash_process(sle, next_close);
	if (vct_charat(sle->line, *i) == '\0')
		return (brace_exp_process(next_close, i));
	else if (vct_charat(sle->line, *i) == '}')
		*next_close = IS_CLOSE;
	return (0);
}

static uint64_t	single_quote_routine(t_sle *sle, size_t *i, uint16_t *next_close)
{
	if (vct_charat(sle->line, *i) == '\0')
		return (single_quote_process(next_close, i));
	else if (vct_charat(sle->line, *i) == '\'')
		*next_close = IS_CLOSE;
	return (0);
}

static uint64_t	double_quote_routine(t_sle *sle, size_t *i, uint16_t *next_close)
{
	if (vct_charat(sle->line, *i) == '\0')
		return (double_quote_process(next_close, i));
	else if (is_brace_exp(sle, *i) == TRUE)
	{
		*next_close = SP_BRACE_EXP;
		(*i)++;
	}
	else if (is_maths_exp(sle, *i) == TRUE)
	{
		*next_close = SP_MATHS_EXP;
		(*i) += 2;
	}
	else if (vct_charat(sle->line, *i) == '\"')
		*next_close = IS_CLOSE;
	else if (vct_charat(sle->line, *i) == '\\')
		(*i)++;
	return (0);
}


static uint64_t	any_routine(t_sle *sle, size_t *i, uint16_t *next_close)
{
	if (vct_charat(sle->line, *i) == '\0')
		*next_close = IS_CLOSE;
	else if (is_end_backslash(sle, *i) == TRUE)
		return (backslash_process(sle, next_close));
	else if (is_brace_exp(sle, *i) == TRUE)
	{
		*next_close = SP_BRACE_EXP;
		(*i)++;
	}
	else if (is_maths_exp(sle, *i) == TRUE)
	{
		*next_close = SP_MATHS_EXP;
		(*i) += 2;
	}
	else if (vct_charat(sle->line, *i) == '\'')
		*next_close = SP_SINGLE_QUOTE;
	else if (vct_charat(sle->line, *i) == '\"')
		*next_close = SP_DOUBLE_QUOTE;
	else if (vct_charat(sle->line, *i) == '\\')
		(*i)++;
	return (0);
}

uint16_t			verif_line(t_registry *shell, t_sle *sle, size_t i,
						uint16_t close)
{
	uint64_t	option;
	uint16_t	next_close;

	if (close == IS_CLOSE)
		return (IS_CLOSE);
	option = 0;
	next_close = close;
	if (close == ANY)
		option = any_routine(sle, &i, &next_close);
	else if (close == SP_SINGLE_QUOTE)
		option = single_quote_routine(sle, &i, &next_close);
	else if (close == SP_DOUBLE_QUOTE)
		option = double_quote_routine(sle, &i, &next_close);
	else if (close == SP_BRACE_EXP)
		option = brace_exp_routine(sle, &i, &next_close);
	else if (close == SP_MATHS_EXP)
		option = maths_exp_routine(sle, &i, &next_close);
	if (option != 0)
	{
		subprompt_call(shell, sle, option);
		return (verif_line(shell, sle, i, next_close));
	}
	return (verif_line(shell, sle, i + 1, next_close));
}
