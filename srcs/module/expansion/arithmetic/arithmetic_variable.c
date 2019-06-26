/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 07:20:23 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/26 07:20:39 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		m_variable_analyzer(t_arithmetic *arithmetic)
{
	arithmetic->state = MATH_VARIABLE;
	ft_stckpushnode(&arithmetic->processing, arithmetic->current);
	m_get_token(arithmetic, NULL);
	if (arithmetic->curr_token->type == E_M_DELIMITER)
		m_get_token(arithmetic, &arithmetic->current);
}

void		m_flush_variable_analyzer(t_arithmetic *arithmetic)
{
	t_list		*node;
	t_rpn_tk	token;
	t_token		*current;
	char		*data;

	arithmetic->state = MATH_VARIABLE_FLUSH;
	ft_bzero(&token, sizeof(t_rpn_tk));
	node = ft_stckpopnode(&arithmetic->processing);
	current = node->data;
	token.type = RPN_NUMBER;
	if ((data = get_var(g_shell->intern, current->data)))
		token.value.digit = ft_atoll_base(data, DEC_BASE);
	else
		token.value.digit = 0;
	ft_lstdelone(&node, NULL);
	node = ft_lstnew(&token, sizeof(t_rpn_tk));
	if (arithmetic->parenthesis > 0)
		ft_stckpushnode(&arithmetic->processing, node);
	else
		ft_lstaddback(&arithmetic->solving, node);
}
