/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 20:16:09 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/02 18:25:11 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		delete_character(char *str)
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

static int	delete_backslash(char *str, t_quote quote)
{
	if (quote == QUOTE_DOUBLE)
	{
		if (ft_strchr(BACKSLASH_DQUOTE, str[1]))
		{
			delete_character(str);
			return (TRUE);
		}
		else
			return (FALSE);
	}
	else
	{
		delete_character(str);
		return (TRUE);
	}
}

void		quote_removal(char *str)
{
	t_quote		quote;

	quote = 0;
	while (*str != '\0')
	{
		if (ft_strchr("\'\"", *str))
			quote = select_quoting(quote, *str);
		if (*str == '\\' && (quote == QUOTE_OFF || quote == QUOTE_DOUBLE))
		{
			if (delete_backslash(str, quote) == TRUE)
				str++;
		}
		if (quote != QUOTE_DOUBLE && *str == '\'')
			delete_character(str);
		else if (quote != QUOTE_SINGLE && *str == '\"')
			delete_character(str);
		else
			++str;
	}
}
