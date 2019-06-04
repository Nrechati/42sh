/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 00:58:53 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/04 17:55:33 by skuppers         ###   ########.fr       */
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

char	*string_expansion(t_resolution *resolve, char *str)
{
	resolve->special_case ^= QUOTING;
	str = tilde(resolve, str);
	str = variable_expansion(resolve, str);
	quote_removal(str);
	resolve->special_case ^= QUOTING;
	return (str);
}
