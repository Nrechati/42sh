/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_preffix_plus_minus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 07:18:30 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/26 07:19:51 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		m_preffix_plus_minus_analyzer(t_arithmetic *arithmetic)
{
	ft_stckpushnode(&arithmetic->sign, arithmetic->current);
	if (arithmetic->curr_token->type == E_M_PLUS)
		arithmetic->state = MATH_PREFIX_PLUS;
	else
		arithmetic->state = MATH_PREFIX_MINUS;
	m_get_token(arithmetic, NULL);
}

void		m_double_preffix_plus_analyzer(t_arithmetic *arithmetic)
{
	arithmetic->state = MATH_PREFFIX_DOUBLE_PLUS;
	m_get_token(arithmetic, NULL);
	if (arithmetic->curr_token->type == E_M_DELIMITER)
		m_get_token(arithmetic, &arithmetic->current);
}

void		m_double_preffix_minus_analyzer(t_arithmetic *arithmetic)
{
	arithmetic->state = MATH_PREFFIX_DOUBLE_MINUS;
	m_get_token(arithmetic, NULL);
	if (arithmetic->curr_token->type == E_M_DELIMITER)
		m_get_token(arithmetic, &arithmetic->current);
}

void		convert_plus_minus(t_token *token, t_rpn_tk *current)
{
	if (token->type == E_M_PLUS)
		current->value.type |= (PLUS | LOW);
	else if (token->type == E_M_MINUS)
		current->value.type |= (MINUS | LOW);
}

void		m_flush_preffix_sign_analyzer(t_arithmetic *arithmetic)
{
	t_list		*node;
	t_rpn_tk	token;


	node = ft_stckpopnode(&arithmetic->sign);
	arithmetic->state = MATH_FLUSH_PREFFIX_SIGN;
	ft_bzero(&token, sizeof(t_rpn_tk));
	token.type = RPN_OPERATOR;
	convert_plus_minus(node->data, &token);
	ft_lstdelone(&node, NULL);
	if (arithmetic->parenthesis > 0)
		ft_stckpushnode(&arithmetic->processing, node);
	else
		ft_lstaddback(&arithmetic->solving, node);
	if (arithmetic->curr_token->type == E_M_DELIMITER)
		m_get_token(arithmetic, &arithmetic->current);
}

void		m_preffix_delimiter_analyzer(t_arithmetic *arithmetic)
{
	arithmetic->state = MATH_PREFFIX_DELIMITER;
}

void		m_preincrement_analyzer(t_arithmetic *arithmetic)
{
	t_list		*node;
	t_rpn_tk	token;
	t_token		*current;
	char		*data;

	arithmetic->state = MATH_PREINCREMENT;
	ft_bzero(&token, sizeof(t_rpn_tk));
	current = arithmetic->curr_token;
	token.type = RPN_NUMBER;
	if ((data = get_var(g_shell->intern, current->data)))
	{
		token.value.digit = ft_atoll_base(data, DEC_BASE) + 1;
		data = ft_llitoa(token.value.digit);
	}
	else
	{
		data = ft_strdup("1");
		token.value.digit = 1;
	}
	add_var(&g_shell->intern, current->data, data, SET_VAR);
	ft_strdel(&data);
	ft_lstdelone(&arithmetic->current, NULL);
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	if (arithmetic->parenthesis > 0)
		ft_stckpushnode(&arithmetic->processing, node);
	else
		ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic, NULL);
	if (arithmetic->curr_token->type == E_M_DELIMITER)
		m_get_token(arithmetic, &arithmetic->current);
}

void		m_predecrement_analyzer(t_arithmetic *arithmetic)
{
	t_list		*node;
	t_rpn_tk	token;
	t_token		*current;
	char		*data;

	arithmetic->state = MATH_PREDECREMENT;
	ft_bzero(&token, sizeof(t_rpn_tk));
	current = arithmetic->curr_token;
	token.type = RPN_NUMBER;
	if ((data = get_var(g_shell->intern, current->data)))
	{
		token.value.digit = ft_atoll_base(data, DEC_BASE) - 1;
		data = ft_llitoa(token.value.digit);
	}
	else
	{
		data = ft_strdup("-1");
		token.value.digit = -1;
	}
	add_var(&g_shell->intern, current->data, data, SET_VAR);
	ft_strdel(&data);
	ft_lstdelone(&arithmetic->current, NULL);
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	if (arithmetic->parenthesis > 0)
		ft_stckpushnode(&arithmetic->processing, node);
	else
		ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic, NULL);
	if (arithmetic->curr_token->type == E_M_DELIMITER)
		m_get_token(arithmetic, &arithmetic->current);
}
