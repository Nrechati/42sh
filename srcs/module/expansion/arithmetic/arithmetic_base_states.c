/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_base_states.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 22:40:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/26 03:00:24 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

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
	if (arithmetic->parenthesis > 0)
		ft_stckpushnode(&arithmetic->processing, node);
	else
		ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic, NULL);
//	if (arithmetic->curr_token->type == E_M_DELIMITER)
//		m_get_token(arithmetic, &arithmetic->current);
}

void		apply_preffix(t_token *preffix, t_rpn_tk *token)
{
	if (preffix->type == E_M_PLUS)
		token->value.digit *= 1;
	else
		token->value.digit *= -1;
}

void		m_preffixed_number_analyzer(t_arithmetic *arithmetic)
{
	t_list			*node;
	t_rpn_tk		token;

	ft_bzero(&token, sizeof(t_rpn_tk));
	arithmetic->state = MATH_PREFFIXED_NUMBER;
	token.type = RPN_NUMBER;
	convert_number(&token, arithmetic->curr_token);
	ft_lstdelone(&arithmetic->current, del_token);
	arithmetic->curr_token = NULL;
	node = ft_stckpopnode(&arithmetic->sign);
	apply_preffix(node->data, &token);
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	if (arithmetic->parenthesis > 0)
		ft_stckpushnode(&arithmetic->processing, node);
	else
		ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic, NULL);
//	if (arithmetic->curr_token->type == E_M_DELIMITER)
//		m_get_token(arithmetic, &arithmetic->current);

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
	if (arithmetic->parenthesis > 0)
		ft_stckpushnode(&arithmetic->processing, node);
	else
		ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic, NULL);
//	if (arithmetic->curr_token->type == E_M_DELIMITER)
//		m_get_token(arithmetic, &arithmetic->current);
}

void		m_parenthesis_analyzer(t_arithmetic *arithmetic)
{
	t_list			*node;
	t_rpn_tk		token;

	ft_bzero(&token, sizeof(t_rpn_tk));
	if (arithmetic->curr_token->type == E_M_OPENP)
	{
		arithmetic->state = MATH_OPEN_PARENT;
		arithmetic->parenthesis++;
		token.type = RPN_PARENT_OPEN;
	}
	else
	{
		arithmetic->state = MATH_CLOSE_PARENT;
		arithmetic->parenthesis++;
		token.type = RPN_PARENT_CLOSE;
	}
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	ft_lstdelone(&arithmetic->current, del_token);
	arithmetic->curr_token = NULL;
	ft_stckpushnode(&arithmetic->processing, node);
	m_get_token(arithmetic, NULL);
}
