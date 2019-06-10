/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 00:58:53 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/07 16:08:37 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	character_swap(const char swapped)
{
	static char previous = '\0';
	char		c;

	c = previous;
	previous = swapped;
	return (c);
}

t_quote	select_quoting(t_quote quote, const char c)
{
	if (quote == QUOTE_OFF)
		quote = c == '\'' ? QUOTE_SINGLE : QUOTE_DOUBLE;
	else if (quote == QUOTE_SINGLE)
		quote = c == '\'' ? QUOTE_OFF : QUOTE_SINGLE;
	else if (quote == QUOTE_DOUBLE)
		quote = c == '\"' ? QUOTE_OFF : QUOTE_DOUBLE;
	return (quote);
}

char	*expansion_pipeline(t_list *intern_var, char *str)
{
	str = tilde(intern_var, str);
	str = variable_expansion(intern_var, str);
	quote_removal(str);
	return (str);
}
