/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_analyzer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:13:50 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/25 17:48:48 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		m_get_token(t_arithmetic *arithmetic)
{
	arithmetic->current = arithmetic->tokens;
	arithmetic->tokens = arithmetic->tokens->next;
	arithmetic->current->next = NULL;
	arithmetic->curr_token = arithmetic->current->data;
}


void		convert_number(t_rpn_tk *current, t_token *token)
{
	size_t		control;

	if (token->type == E_M_NB_OCT)
	{
		control = ft_strspn(token->data, OCTAL_BASE);
		if (token->data[control] != '\0')
			; //error
		else
			current->value.digit = ft_atoll_base(token->data, OCTAL_BASE);
	}
	else if (token->type == E_M_NB_HEX)
	{
		ft_strupper(token->data);
		current->value.digit = ft_atoll_base(token->data + 2, HEX_BASE);
	}
	else
		current->value.digit = ft_atoll_base(token->data, DEC_BASE);

}

void		m_number_analyzer(t_arithmetic *arithmetic)
{
	t_list			*node;
	t_rpn_tk		token;

	ft_bzero(&token, sizeof(t_rpn_tk));
	arithmetic->state = MATH_NUMBER;
	token.type = RPN_NUMBER;
	convert_number(&token, arithmetic->curr_token);
	ft_lstdelone(&arithmetic->current, del_token);
	arithmetic->curr_token = NULL;
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic);
}

void		m_parenthesis_analyzer(t_arithmetic *arithmetic)
{
	t_list			*node;
	t_rpn_tk		token;

	ft_bzero(&token, sizeof(t_rpn_tk));
	if (arithmetic->curr_token->type == E_M_OPENP)
	{
		arithmetic->state = MATH_OPEN_PARENT;
		token.type = RPN_PARENTHESIS;
	}
	else
	{
		arithmetic->state = MATH_CLOSE_PARENT;
		token.type = RPN_PARENTHESIS;
	}
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	ft_lstdelone(&arithmetic->current, del_token);
	arithmetic->curr_token = NULL;
	ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic);
}

void		convert_operator(t_arithmetic *arithmetic, t_rpn_tk *token)
{
	if (arithmetic->curr_token->type == E_M_PLUS)
		token->value.type |= (PLUS | LOW);
	else if (arithmetic->curr_token->type == E_M_MINUS)
		token->value.type |= (MINUS | LOW);
	else if (arithmetic->curr_token->type == E_M_TIMES)
		token->value.type |= (TIMES | HIGH);
	else if (arithmetic->curr_token->type == E_M_DIVIDE)
		token->value.type |= (DIVIDE | HIGH);
	else if (arithmetic->curr_token->type == E_M_MODULO)
		token->value.type |= (MODULO | HIGH);
}

void		m_operator_analyzer(t_arithmetic *arithmetic)
{
	t_list			*node;
	t_rpn_tk		token;

	ft_bzero(&token, sizeof(t_rpn_tk));
	arithmetic->state = MATH_OPERATOR;
	token.type = RPN_OPERATOR;
	convert_operator(arithmetic, &token);
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	ft_lstdelone(&arithmetic->current, del_token);
	arithmetic->curr_token = NULL;
	ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic);
}

void		m_variable_analyzer(t_arithmetic *arithmetic)
{
	arithmetic->state = MATH_VARIABLE;
	ft_stckpushnode(&arithmetic->processing, arithmetic->current);
	m_get_token(arithmetic);
}

void		m_plus_minus_analyzer(t_arithmetic *arithmetic)
{
	ft_stckpushnode(&arithmetic->processing, arithmetic->current);
	if (arithmetic->curr_token->type == E_M_PLUS)
		arithmetic->state = MATH_PLUS;
	else
		arithmetic->state = MATH_MINUS;
	m_get_token(arithmetic);
}

void		m_error_analyzer(t_arithmetic *arithmetic)
{
	arithmetic->state = MATH_ERROR;
	ft_dprintf(2, "42sh: %s : error token near %s "
			, arithmetic->input->buffer
			, arithmetic->curr_token->data);
}

void		m_end_analyzer(t_arithmetic *arithmetic)
{
	arithmetic->state = MATH_END;
	ft_lstdelone(&arithmetic->current, del_token);
	arithmetic->curr_token = NULL;
}

char		*package_expression(t_arithmetic *arithmetic)
{
	char		*output;
	t_infix		infix;

	output = NULL;
	ft_bzero(&infix, sizeof(t_infix));
	if (ft_stcksize(&arithmetic->processing) > 0)
		;
	else
		infix.type = 0;
	infix.calcul.size = ft_lstlen(arithmetic->solving);
	infix.calcul.head = arithmetic->solving;
	if (calculator(&infix) == FAILURE)
		return (NULL);
	ft_asprintf(&output, "%ld", infix.result);
	return (output);
}

int8_t		arithmetic_analyzer(t_arithmetic *arithmetic)
{
	static t_ar_analyzer	*analyzer = NULL;

	if (analyzer == NULL)
		analyzer = init_math_analyzer();
	m_get_token(arithmetic);
	while (arithmetic->state != MATH_END && arithmetic->state != MATH_ERROR)
		(*analyzer)[arithmetic->state][arithmetic->curr_token->type](arithmetic);
	arithmetic->expanded = package_expression(arithmetic);
	if (arithmetic->expanded == NULL)
		return (FAILURE);
	return (SUCCESS);
}
