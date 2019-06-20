/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_subroutine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 14:58:14 by ffoissey          #+#    #+#             */
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

static uint64_t backslash_process(t_sle *sle)
{
	vct_pop(sle->line);
	vct_pop(sle->line);
	return (PRINT_NL);
}

void	maths_exp_routine(t_sle *sle, size_t *i)
{
	while (vct_charat(sle->line, *i) != ')'
			&& vct_charat(sle->line, *i + 1) != ')')
	{
		if (vct_charat(sle->line, *i) == '\0')
			subprompt_call(sle, PRINT_MATHS);
		else
			(*i)++;
	}
}

void	brace_exp_routine(t_sle *sle, size_t *i)
{
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
		{
			(*i)++;
			ft_putendl("hey");
			double_quote_routine(sle, i);
		}
		(*i)++;
	}
}

void	single_quote_routine(t_sle *sle, size_t *i)
{
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
	while (vct_charat(sle->line, *i) != '\"')
	{
		if (vct_charat(sle->line, *i) == '\0')
		{
			ft_putendl("wefwef");
			subprompt_call(sle, PRINT_DQUOTE);
			continue ;
		}
		else if (is_brace_exp(sle, *i) == TRUE)
		{
			(*i) += 2;
			brace_exp_routine(sle, i);
		}
		else if (is_maths_exp(sle, *i) == TRUE)
		{
			(*i) += 3;
			maths_exp_routine(sle, i);
		}
		else if (vct_charat(sle->line, *i) == '\\')
			(*i)++;
		(*i)++;
	}
}


void	any_routine(t_sle *sle, size_t *i)
{
	while (vct_charat(sle->line, *i) != '\0')
	{
		if (is_end_backslash(sle, *i) == TRUE)
		{
			backslash_process(sle);
			subprompt_call(sle, PRINT_NL);
			continue ;
		}
		else if (is_brace_exp(sle, *i) == TRUE)
		{
			(*i) += 2;
			brace_exp_routine(sle, i);
		}
		else if (is_maths_exp(sle, *i) == TRUE)
		{
			(*i) += 3;
			maths_exp_routine(sle, i);
		}
		else if (vct_charat(sle->line, *i) == '\'')
		{
			(*i)++;
			single_quote_routine(sle, i);
		}
		else if (vct_charat(sle->line, *i) == '\"')
		{
			(*i)++;
			double_quote_routine(sle, i);
		}
		else if (vct_charat(sle->line, *i) == '\\')
			(*i)++;
		(*i)++;
	}
}

void				verif_line(t_sle *sle)
{
	size_t		i;

	i = 0;
	any_routine(sle, &i);
}
