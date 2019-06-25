/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_analyzer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:13:50 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/25 14:11:08 by nrechati         ###   ########.fr       */
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

void		m_number_analyzer(t_arithmetic *arithmetic)
{
	arithmetic->state = MATH_NUMBER;
	ft_stckpushnode(&arithmetic->processing, arithmetic->current);
	m_get_token(arithmetic);
}

void		m_error_analyzer(t_arithmetic *arithmetic)
{
}

t_list		*arithmetic_analyzer(t_arithmetic *arithmetic)
{
	static t_ar_analyzer	*analyzer = NULL;
	t_list					*math_group;

	if (analyzer == NULL)
		analyzer = init_math_analyzer();
	m_get_token(arithmetic);
}
