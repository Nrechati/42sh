/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_subroutine_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:48:14 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/02 19:48:40 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

uint8_t			single_quote_routine(t_sle *sle, t_vector *line, size_t *i)
{
	(*i)++;
	while (vct_charat(line, *i) != '\'')
	{
		if (vct_charat(line, *i) == '\0')
		{
			if (subprompt_call(sle, line, PRINT_QUOTE) == FALSE)
				return (FALSE);
		}
		else
			(*i)++;
	}
	return (TRUE);
}

uint8_t			double_quote_routine(t_sle *sle, t_vector *line, size_t *i)
{
	uint8_t	ret;

	(*i)++;
	ret = TRUE;
	while (vct_charat(line, *i) != '\"')
	{
		if (vct_charat(line, *i) == '\0')
		{
			if (subprompt_call(sle, line, PRINT_DQUOTE) == FALSE)
				return (FALSE);
			continue ;
		}
		else if (is_brace_exp(line, *i) == TRUE)
			ret = brace_exp_routine(sle, line, i);
		else if (is_maths_exp(line, *i) == TRUE)
			ret = maths_exp_routine(sle, line, i);
		else if (vct_charat(line, *i) == '\\')
			(*i)++;
		if (ret == FALSE)
			return (FALSE);
		(*i)++;
	}
	return (TRUE);
}
