/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 12:58:54 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/02 17:03:03 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int			arithmetic_replace(t_arithmetic *arithmetic, char **output, int i)
{
	t_vector *vector;

	vector = vct_dups(*output);
	vct_replace_string(vector, i, i + arithmetic->end + 1, arithmetic->expanded);
	ft_strdel(output);
	*output = ft_strdup(vct_get_string(vector));
	vct_del(&vector);
	return (0);
}

static int	arithmetic(char **output, int i)
{
	t_arithmetic	arithmetic;

	ft_bzero(&arithmetic, sizeof(t_arithmetic));
	if (find_expansion_end(&arithmetic, *output, i + 3) == FAILURE)
		return (FAILURE);
	if (get_expansion_input(&arithmetic, *output, i + 3) == FAILURE)
		return (FAILURE);
	arithmetic.tokens = lexer(arithmetic.input, MATHS);
	if (arithmetic_analyzer(&arithmetic) == FAILURE)
		return (FAILURE);
	arithmetic_replace(&arithmetic, output, i);
	del_arithmetic(&arithmetic);
	return (1);
}

static int	check_math_expansion(char **buff, int i)
{
	char	*input;
	int		check;

	check = 0;
	input = *buff;
	if (input[i] != '$')
		return (0);
	if (ft_strnequ(&input[i + 1], "((", 2) == TRUE)
		check = arithmetic(buff, i);
	return (check);
}

char		*arithmetic_expansion(char *input)
{
	uint32_t	i;
	uint32_t	len;
	t_quote		quote;
	char		*dest;
	int			result;

	i = 0;
	quote = 0;
	dest = ft_strdup(input);
	len = ft_strlen(dest);
	while (i < len)
	{
		if (ft_strchr("\'\"", dest[i]))
			quote = select_quoting(quote, dest[i]);
		if (dest[i] == '\\' && (quote == QUOTE_OFF || quote == QUOTE_DOUBLE))
			i = check_backslash(dest, quote, i);
		else if ((result = check_math_expansion(&dest, i)) == 1)
			len = ft_strlen(dest);
		else if (result == -1)
			return (NULL);
		++i;
	}
	return (dest);
}
