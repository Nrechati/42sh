/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 12:58:54 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/24 10:17:38 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	print_token_lst(t_arithmetic *math)
{
	t_list	*ptr;
	t_math	*token;

	ptr = math->tokens;
	while (ptr != NULL)
	{
		token = ptr->data;
		ft_printf("|| %s | %d || ->", token->value, token->type);
		ptr = ptr->next;
	}
	ft_printf("NULL \n");
}

int		ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'
			|| c == '\r' || c == '\v' || c == '\f')
		return (1);
	else
		return (0);
}

void		trim_space(t_arithmetic *math)
{
	while (ft_isspace(math->source[math->index]) == TRUE)
		math->index++;
}

void		out_math(t_arithmetic *math)
{
	t_math		token;
	t_list		*node;

	node = NULL;
	ft_bzero(&token, sizeof(t_math));
	token.type = math->type;
	token.value = ft_strdup(math->buffer->buffer);
	node = ft_lstnew(&token, sizeof(t_math));
	ft_lstaddback(&math->tokens, node);
	vct_del(&math->buffer);
	math->buffer = vct_new(DEFAULT_BUFFER);
	math->state = MATH_START;
}

void		hexa_math(t_arithmetic *math)
{
	if (ft_strchr(HEXA_CHARSET, math->source[math->index]) == NULL)
	{
		math->state = MATH_OUT;
		math->type = TYPE_HEXA;
	}
	else
	{
		vct_add(math->buffer, math->source[math->index]);
		math->index++;
	}
}

void		octal_math(t_arithmetic *math)
{
	if (ft_strchr("xX", math->source[math->index]) && math->buffer->size == 1)
	{
		math->state = MATH_HEXA;
		vct_add(math->buffer, math->source[math->index]);
		math->index++;
	}
	else if (ft_strchr(OCTAL_CHARSET, math->source[math->index]) == NULL)
	{
		math->state = MATH_OUT;
		math->type = TYPE_OCTAL;
	}
	else
	{
		vct_add(math->buffer, math->source[math->index]);
		math->index++;
	}
}

void		decimal_math(t_arithmetic *math)
{
	if (ft_isdigit(math->source[math->index]) == FALSE)
	{
		math->state = MATH_OUT;
		math->type = TYPE_DECIMAL;
	}
	else if (math->source[math->index] == '0' && math->buffer->buffer == '\0')
	{
		math->state = MATH_OCTAL;
		vct_add(math->buffer, math->source[math->index]);
		math->index++;
	}
	else
	{
		vct_add(math->buffer, math->source[math->index]);
		math->index++;
	}
}

void		variable_math(t_arithmetic *math)
{
	if (math->buffer->size == 0
			&& (ft_isalpha(math->source[math->index]) == TRUE
			|| math->source[math->index] == '_'))
	{
		vct_add(math->buffer, math->source[math->index]);
		math->index++;
	}
	else if (ft_isalnum(math->source[math->index]) == TRUE
			|| math->source[math->index] == '_')
	{
		vct_add(math->buffer, math->source[math->index]);
		math->index++;
	}
	else
	{
		math->state = MATH_OUT;
		math->type = TYPE_VARIABLE;
	}
}

void		sign_math(t_arithmetic *math)	// * / %
{
	if (ft_strequ(math->source + math->index, "))"))
	{
		math->state = MATH_END;
		return ;
	}
	if (ft_strchr(SINGLE_SIGN_SET, math->source[math->index]))
	{
		if (math->source[math->index] == '*')
			math->type = TYPE_TIME;
		else if (math->source[math->index] == '/')
			math->type = TYPE_DIVIDE;
		else if (math->source[math->index] == '%')
			math->type = TYPE_MODULO;
		else if (math->source[math->index] == '(')
			math->type = TYPE_OPEN_P;
		else if (math->source[math->index] == ')')
			math->type = TYPE_CLOSE_P;
		vct_add(math->buffer, math->source[math->index]);
		math->index++;
		math->state = MATH_OUT;
		return ;
	}
	vct_add(math->buffer, math->source[math->index]);
	math->index++;
	if (math->buffer->buffer[0] == '+')
	{
		if (math->source[math->index] == '+')
		{
			math->type = TYPE_INCREMENT;
			math->index++;
		}
		else
			math->type = TYPE_ADD;
	}
	else if (math->buffer->buffer[0] == '-')
	{
		if (math->source[math->index] == '-')
		{
			math->type = TYPE_DECREMENT;
			math->index++;
		}
		else
			math->type = TYPE_SUBSTRACT;
	}
	math->state = MATH_OUT; // OK ?
	return ;
}

void		logical_math(t_arithmetic *math)
{
	vct_add(math->buffer, math->source[math->index]);
	math->index++;
	if (math->buffer->buffer[0] == '<')
	{
		if (math->source[math->index] == '=')
		{
			math->type = TYPE_LOWER_OR;
			math->index++;
		}
		else
			math->type = TYPE_LOWER;
	}
	else if (math->buffer->buffer[0] == '>')
	{
		if (math->source[math->index] == '=')
		{
			math->type = TYPE_GREATER_OR;
			math->index++;
		}
		else
			math->type = TYPE_GREATER;
	}
	else if (math->buffer->buffer[0] == '!')
	{
		if (math->source[math->index] == '=')
		{
			math->type = TYPE_NOT_EQUAL;
			math->index++;
		}
		else
			math->type = TYPE_ERROR;
	}
	else if (math->buffer->buffer[0] == '=')
	{
		if (math->source[math->index] == '=')
		{
			math->type = TYPE_EQUAL;
			math->index++;
		}
		else
			math->type = TYPE_ASSIGN;
	}
	else if (math->buffer->buffer[0] == '&')
	{
		if (math->source[math->index] == '&')
		{
			math->type = TYPE_AND;
			math->index++;
		}
		else
			math->type = TYPE_ERROR;
	}
	else if (math->buffer->buffer[0] == '|')
	{
		if (math->source[math->index] == '|')
		{
			math->type = TYPE_OR;
			math->index++;
		}
		else
			math->type = TYPE_ERROR;
	}
	math->state = MATH_OUT;
	return ;
}

void		start_math(t_arithmetic *math)
{
	if (ft_isspace(math->source[math->index]) == TRUE)
		trim_space(math);
	if (ft_isdigit(math->source[math->index]) == TRUE)
		math->state = MATH_DECIMAL;
	else if (ft_isalpha(math->source[math->index]) == TRUE)
		math->state = MATH_VARIABLE;
	else if (ft_strchr(SIGN_SET, math->source[math->index]))
		math->state = MATH_SIGN;
	else if (ft_strchr(LOGICAL_SET, math->source[math->index]))
		math->state = MATH_LOGICAL;
}

static void	init_mathexp(t_mathexp state[MATH_STATES])
{
	state[MATH_START] = start_math;
	state[MATH_DECIMAL] = decimal_math;
	state[MATH_OCTAL] = octal_math;
	state[MATH_HEXA] = hexa_math;
	state[MATH_VARIABLE] = variable_math;
	state[MATH_SIGN] = sign_math;
	state[MATH_LOGICAL] = logical_math;
	state[MATH_OUT] = out_math;
	state[MATH_END] = NULL;
}

void		arithmetic_lexer(t_arithmetic *math)
{
	static t_mathexp	state[MATH_STATES];

	if (state[0] == NULL)
		init_mathexp(state);
	while (math->state != MATH_END)
		state[math->state](math);
	print_token_lst(math);
}

int			arithmetic(__unused t_list *intern, char **output, int i)
{
	t_arithmetic	math;

	ft_bzero(&math, sizeof(t_arithmetic));
	math.source = *output + i;
	math.index = 3;
	math.buffer = vct_new(DEFAULT_BUFFER);
	arithmetic_lexer(&math);
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
