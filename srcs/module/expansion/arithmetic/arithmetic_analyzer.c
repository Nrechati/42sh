/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_analyzer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:13:50 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/25 23:13:24 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

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

void		m_preffix_plus_minus_analyzer(t_arithmetic *arithmetic)
{
	ft_stckpushnode(&arithmetic->sign, arithmetic->current);
	if (arithmetic->curr_token->type == E_M_PLUS)
		arithmetic->state = MATH_PREFIX_PLUS;
	else
		arithmetic->state = MATH_PREFIX_MINUS;
	m_get_token(arithmetic);
}

void		m_double_plus_analyzer(t_arithmetic *arithmetic)
{
	arithmetic->state = MATH_DOUBLE_PLUS;

}

void		convert_plus_minus(t_token *token, t_rpn_tk *current)
{
	if (token->type == E_M_PLUS)
		current->value.type |= (PLUS | LOW);
	else if (token->type == E_M_MINUS)
		current->value.type |= (MINUS | LOW);
}

void		m_flush_sign_analyzer(t_arithmetic *arithmetic)
{
	t_list		*node;
	t_rpn_tk	token;

	node = ft_stckpopnode(&arithmetic->sign);
	ft_bzero(&token, sizeof(t_rpn_tk));
	token.type = RPN_OPERATOR;
	convert_plus_minus(node->data, &token);
	ft_lstdelone(&node, NULL);
	if (arithmetic->parenthesis > 0)
		ft_stckpushnode(&arithmetic->processing, node);
	else
		ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic);
	if (arithmetic->curr_token->type == E_M_DELIMITER)
		m_get_token(arithmetic);
}

void		m_stop_analyzer(t_arithmetic *arithmetic)
{
	arithmetic->state = MATH_STOP;
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

void		flush_processing(t_arithmetic *arithmetic, t_infix *infix)
{
	t_list		*node;
	t_rpn_tk	*token;

	node = NULL;
	token = NULL;
	while (token->type != RPN_PARENT_OPEN)
	{
		node = ft_stckpopnode(&arithmetic->processing);
		token = node->data;
		ft_lstadd(&infix->calcul.head, node);
	}
}

int8_t		push_solution(t_arithmetic *arithmetic, t_infix *infix)
{
	t_list 			*node;
	t_rpn_tk		token;

	token.type = RPN_NUMBER;
	infix->calcul.size = ft_lstlen(arithmetic->solving);
	infix->calcul.head = arithmetic->solving;
	arithmetic->solving = NULL;
	if (calculator(infix) == FAILURE)
		return (FAILURE);
	token.value.digit = infix->result;
	del_infix(infix);
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	ft_lstaddback(&arithmetic->solving, node);
	return (SUCCESS);
}

void		process_current_arithmetic(t_arithmetic *arithmetic)
{
	t_infix		infix;

	ft_bzero(&infix, sizeof(t_infix));
	if (arithmetic->parenthesis)
		flush_processing(arithmetic, &infix);
	else
		push_solution(arithmetic, &infix);
}

int8_t		arithmetic_analyzer(t_arithmetic *arithmetic)
{
	static t_ar_analyzer	*analyzer = NULL;

	if (analyzer == NULL)
		analyzer = init_math_analyzer();
	m_get_token(arithmetic);
	while (arithmetic->state != MATH_END && arithmetic->state != MATH_ERROR)
	{
		if (arithmetic->state == MATH_STOP)
			process_current_arithmetic(arithmetic);
		(*analyzer)[arithmetic->state][arithmetic->curr_token->type](arithmetic);
	}
	arithmetic->expanded = package_expression(arithmetic);
	if (arithmetic->expanded == NULL)
		return (FAILURE);
	return (SUCCESS);
}
