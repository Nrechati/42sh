/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_preffix_plus_minus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 07:18:30 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/27 18:18:07 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		m_preincrement_analyzer(t_arithmetic *arithmetic)
{
	t_list		*node;
	t_rpn_tk	token;
	t_token		*current;
	char		*data;

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
	ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic, NULL);
}

void		m_predecrement_analyzer(t_arithmetic *arithmetic)
{
	t_list		*node;
	t_rpn_tk	token;
	t_token		*current;
	char		*data;

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
	ft_lstaddback(&arithmetic->solving, node);
	m_get_token(arithmetic, NULL);
}

void		m_postincrement_analyzer(t_arithmetic *arithmetic)
{
	t_list		*node;
	t_rpn_tk	token;
	t_token		*current;
	char		*data;

	ft_bzero(&token, sizeof(t_rpn_tk));
	node = ft_stckpopnode(&arithmetic->processing);
	current = node->data;
	token.type = RPN_NUMBER;
	if ((data = get_var(g_shell->intern, current->data)))
	{
		token.value.digit = ft_atoll_base(data, DEC_BASE);
		data = ft_llitoa(token.value.digit + 1);
	}
	else
	{
		data = ft_strdup("1");
		token.value.digit = 0;
	}
	add_var(&g_shell->intern, current->data, data, SET_VAR);
	ft_strdel(&data);
	ft_lstdelone(&node, NULL);
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	ft_lstaddback(&arithmetic->solving, node);
}

void		m_postdecrement_analyzer(t_arithmetic *arithmetic)
{
	t_list		*node;
	t_rpn_tk	token;
	t_token		*current;
	char		*data;

	ft_bzero(&token, sizeof(t_rpn_tk));
	node = ft_stckpopnode(&arithmetic->processing);
	current = node->data;
	token.type = RPN_NUMBER;
	if ((data = get_var(g_shell->intern, current->data)))
	{
		token.value.digit = ft_atoll_base(data, DEC_BASE);
		data = ft_llitoa(token.value.digit - 1);
	}
	else
	{
		data = ft_strdup("-1");
		token.value.digit = 0;
	}
	add_var(&g_shell->intern, current->data, data, SET_VAR);
	ft_strdel(&data);
	ft_lstdelone(&node, NULL);
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	ft_lstaddback(&arithmetic->solving, node);
}

void		m_preffix(t_arithmetic *arithmetic)
{
	int			control;

	arithmetic->state = MATH_PREFFIX;
	control = arithmetic->curr_token->type;
	m_get_token(arithmetic, NULL);
	if (arithmetic->curr_token->type == E_M_STRING)
	{
		if (control == E_M_DPLUS)
			m_preincrement_analyzer(arithmetic);
		else if (control == E_M_DMINUS)
			m_predecrement_analyzer(arithmetic);
		else
			m_error_analyzer(arithmetic);
	}
	else
		m_error_analyzer(arithmetic);
}

void		m_suffix(t_arithmetic *arithmetic)
{
	int			control;
	t_token		*token;

	token = ft_stcktop(&arithmetic->processing);
	arithmetic->state = MATH_SUFFIX;
	control = arithmetic->curr_token->type;
	m_get_token(arithmetic, NULL);
	if (token->type == E_M_STRING)
	{
		if (control == E_M_DPLUS)
			m_postincrement_analyzer(arithmetic);
		else if (control == E_M_DMINUS)
			m_postdecrement_analyzer(arithmetic);
	}
	else
		m_error_analyzer(arithmetic);
}
