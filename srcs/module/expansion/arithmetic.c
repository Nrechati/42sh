/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 12:58:54 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/25 09:43:51 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int	arithmetic(__unused t_list *intern, char **output, int i)
{
	t_list			*token_list;
	t_arithmetic	math;

	token_list = NULL;
	ft_bzero(&math, sizeof(t_arithmetic));
	math.source = *output + i;
	math.index = 3;
	math.buffer = vct_new(DEFAULT_BUFFER);
	token_list = lexer(math.buffer, MATHS);
	return (SUCCESS);
}

static int	check_math_expansion(t_list *intern, char **buff, int i, __unused t_quote quote)
{
	char	*input;
	int		check;

	check = 0;
	input = *buff;
	if (input[i] != '$')
		return (0);
	if (ft_strnequ(&input[i + 1], "((", 2) == TRUE)
		check = arithmetic(intern, buff, i);
	return (check);
}

char		*arithmetic_expansion(t_list *intern, char *input)
{
	uint32_t	i;
	uint32_t	len;
	t_quote		quote;
	char		*output;
	int			result;

	i = 0;
	quote = 0;
	output = ft_strdup(input);
	len = ft_strlen(output);
	while (i < len)
	{
		if (ft_strchr("\'\"", output[i]))
			quote = select_quoting(quote, output[i]);
		if ((result = check_math_expansion(intern, &output, i, quote)) == 1)
			len = ft_strlen(output);
		else if (result == -1)
			return (NULL);
		++i;
	}
	return (output);
}
