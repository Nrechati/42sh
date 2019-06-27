/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 12:58:54 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/26 22:22:02 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int8_t	get_expansion_input(t_arithmetic *arithmetic,  char *input, size_t start)
{
	char		*str;

	str = NULL;
	ft_asprintf(&str, "%.*s", arithmetic->end - start - 1, input + start);
	if (str == NULL)
	{
		ft_dprintf(2, "Malloc Error on get_expansion_input\n");
		return (FAILURE);
	}
	arithmetic->input = vct_dups(str);
	return (SUCCESS);
}

static int8_t	find_expansion_end(t_arithmetic *arithmetic,  char *input, size_t start)
{
	size_t		end;

	end = ft_strcspn(input + start, "$") + start;
	while (end > start)
	{
		if (input[end] == ')' && input[end - 1] == ')')
		{
			arithmetic->end = end;
			return (SUCCESS);
		}
		end--;
	}
	ft_dprintf(2, "No end of expansion token\n");
	return (FAILURE);
}

int				arithmetic_replace(t_arithmetic *arithmetic, char **output, int i)
{
	t_vector *vector;

	vector = vct_dups(*output);
	vct_replace_string(vector, i, i + arithmetic->end + 1, arithmetic->expanded);
	ft_strdel(output);
	*output = ft_strdup(vct_get_string(vector));
	vct_del(&vector);
	return (0);
}

static int		arithmetic(__unused t_list *intern, char **output, int i)
{
	t_arithmetic	arithmetic;

	ft_bzero(&arithmetic, sizeof(t_arithmetic));
	if (find_expansion_end(&arithmetic, *output, i + 3) == FAILURE)
		return (FAILURE);
	if (get_expansion_input(&arithmetic, *output, i + 3) == FAILURE)
		return (FAILURE);
	ft_printf("Expansion buffer : %s\n", arithmetic.input->buffer);
	arithmetic.tokens = lexer(arithmetic.input, MATHS);
	if (arithmetic_analyzer(&arithmetic) == FAILURE)
		return (FAILURE);
	arithmetic_replace(&arithmetic, output, i);
	return (1);
}

static int		check_math_expansion(t_list *intern, char **buff, int i, __unused t_quote quote)
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
		else if ((result = check_math_expansion(intern, &dest, i, quote)) == 1)
			len = ft_strlen(dest);
		else if (result == -1)
			return (NULL);
		++i;
	}
	return (dest);
}
