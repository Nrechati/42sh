/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 20:16:09 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:41:26 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	delete_char(char *str)
{
	char	holder;

	while (str[1] != '\0')
	{
		holder = str[0];
		str[0] = str[1];
		str[1] = holder;
		++str;
	}
	*str = '\0';
}

void		quote_removal(char *str)
{
	t_quote quote;

	quote = 0;
	while (*str != '\0')
	{
		if (ft_strchr("\'\"", *str))
			quote = select_quoting(quote, *str);
		if (quote != QUOTE_DOUBLE && *str == '\'')
			delete_char(str);
		else if (quote != QUOTE_SINGLE && *str == '\"')
			delete_char(str);
		else
			++str;
	}
}
