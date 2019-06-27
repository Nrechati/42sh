/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_base_states.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 22:40:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/27 15:54:27 by nrechati         ###   ########.fr       */
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
	ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic, NULL);
}

void		set_unary(t_token *preffix, t_rpn_tk *token)
{
	if (preffix->type == E_M_PLUS)
		token->value.type |= UNARY_PLUS;
	else
		token->value.type |= UNARY_MINUS;
}

void		m_unary_analyzer(t_arithmetic *arithmetic)
{
	t_list			*node;
	t_rpn_tk		token;

	ft_bzero(&token, sizeof(t_rpn_tk));
	arithmetic->state = MATH_UNARY;
	token.type = RPN_OPERATOR;
	convert_number(&token, arithmetic->curr_token);
	ft_lstdelone(&arithmetic->current, del_token);
	arithmetic->curr_token = NULL;
	node = ft_stckpopnode(&arithmetic->sign);
	set_unary(node->data, &token);
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic, NULL);
}

void		convert_logical_operator(t_arithmetic *arithmetic, t_rpn_tk *token)
{
	if (arithmetic->curr_token->type == E_M_LESS)
		token->value.type |= LESS;
	else if (arithmetic->curr_token->type == E_M_GREAT)
		token->value.type |= GREAT;
	else if (arithmetic->curr_token->type == E_M_LESSEQ)
		token->value.type |= LESSEQ;
	else if (arithmetic->curr_token->type == E_M_GREATEQ)
		token->value.type |= GREATEQ;
	else if (arithmetic->curr_token->type == E_M_EQUAL)
		token->value.type |= EQUAL;
	else if (arithmetic->curr_token->type == E_M_NEQUAL)
		token->value.type |= DIFF;
	else if (arithmetic->curr_token->type == E_M_AND)
		token->value.type |= AND;
	else if (arithmetic->curr_token->type == E_M_OR)
		token->value.type |= OR;
}

void		m_logical_operator(t_arithmetic *arithmetic)
{
	t_list			*node;
	t_rpn_tk		token;

	ft_bzero(&token, sizeof(t_rpn_tk));
	arithmetic->state = MATH_LOGICAL_OPERATOR;
	token.type = RPN_OPERATOR;
	convert_logical_operator(arithmetic, &token);
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	ft_lstdelone(&arithmetic->current, del_token);
	arithmetic->curr_token = NULL;
	ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic, NULL);
}
