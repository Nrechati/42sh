/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_base_states.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 22:40:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/02 17:05:03 by cempassi         ###   ########.fr       */
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
	set_unary(arithmetic->curr_token, &token);
	ft_lstdelone(&arithmetic->current, del_token);
	arithmetic->curr_token = NULL;
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic, NULL);
}
