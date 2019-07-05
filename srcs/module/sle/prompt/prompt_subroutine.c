/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_subroutine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 14:58:14 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/05 11:02:41 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static uint8_t	extend_subroutine(t_sle *sle, t_vector *line, size_t *i,
							uint8_t type)
{
	if (is_end_backslash(line, *i) == TRUE)
		backslash_process(line);
	else if (is_brace_exp(line, *i) == TRUE)
		return (brace_exp_routine(sle, line, i));
	else if (is_maths_exp(line, *i) == TRUE)
		return (maths_exp_routine(sle, line, i));
	else if (vct_charat(line, *i) == '\'')
		return (single_quote_routine(sle, line, i));
	else if (vct_charat(line, *i) == '\"')
		return (double_quote_routine(sle, line, i));
	else if (type == PAR_TYPE && vct_charat(line, *i) == '(')
		return (parenthesis(sle, line, i));
	return (TRUE);
}

uint8_t			parenthesis(t_sle *sle, t_vector *line, size_t *i)
{
	(*i)++;
	while (vct_charat(line, *i) != ')')
	{
		if (vct_charat(line, *i) == '\0')
		{
			if (subprompt_call(sle, line, PRINT_MATHS) == FALSE)
				return (FALSE);
			continue ;
		}
		else if (vct_charat(line, *i) == '\\')
			(*i)++;
		else if (extend_subroutine(sle, line, i, PAR_TYPE) == FALSE)
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
	(*i) += 2;
	while (vct_charat(line, *i) != '}')
	{
		if (vct_charat(line, *i) == '\0')
		{
			if (subprompt_call(sle, line, PRINT_BRACE) == FALSE)
				return (FALSE);
			continue ;
		}
		else if (vct_charat(line, *i) == '\\')
			(*i)++;
		else if (extend_subroutine(sle, line, i, DEFAULT_TYPE) == FALSE)
			return (FALSE);
		(*i)++;
	}
	return (TRUE);
}

uint8_t			verif_line(t_sle *sle, t_vector *line)
{
	size_t		i;

	i = 0;
	while (vct_charat(line, i) != '\0')
	{
		if (is_end_backslash(line, i) == TRUE)
		{
			backslash_process(line);
			if (subprompt_call(sle, line, PRINT_NL) == FALSE)
				return (FALSE);
			continue ;
		}
		else if (vct_charat(line, i) == '\\')
			i++;
		else if (extend_subroutine(sle, line, &i, DEFAULT_TYPE) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
