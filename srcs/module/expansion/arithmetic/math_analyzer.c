/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_analyzer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:31:55 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/25 16:21:39 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void	bzero_analyzer(t_ar_analyzer analyzer)
{
	int		index;
	int		state;

	index = 0;
	while (index < MATH_STATE)
	{
		state = 0;
		while (state < MATH_TOKEN)
			analyzer[index][state++] = m_error_analyzer;
		++index;
	}
}

void init_m_start(t_ar_analyzer analyzer)
{
	analyzer[MATH_START][E_M_NB_DEC] = m_number_analyzer;
	analyzer[MATH_START][E_M_NB_OCT] = m_number_analyzer;
	analyzer[MATH_START][E_M_NB_HEX] = m_number_analyzer;
	analyzer[MATH_START][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_START][E_M_STRING] = m_variable_analyzer;
	analyzer[MATH_START][E_M_PLUS] = m_plus_minus_analyzer;
	analyzer[MATH_START][E_M_MINUS] = m_plus_minus_analyzer;
}

void init_m_number(t_ar_analyzer analyzer)
{
	analyzer[MATH_NUMBER][E_M_TIMES] = m_operator_analyzer;
	analyzer[MATH_NUMBER][E_M_MODULO] = m_operator_analyzer;
	analyzer[MATH_NUMBER][E_M_DIVIDE] = m_operator_analyzer;
	analyzer[MATH_NUMBER][E_M_PLUS] = m_plus_minus_analyzer;
	analyzer[MATH_NUMBER][E_M_MINUS] = m_plus_minus_analyzer;
	analyzer[MATH_NUMBER][E_M_END] = m_end_analyzer;
}

void init_m_operator(t_ar_analyzer analyzer)
{
	analyzer[MATH_OPERATOR][E_M_NB_DEC] = m_number_analyzer;
	analyzer[MATH_OPERATOR][E_M_NB_OCT] = m_number_analyzer;
	analyzer[MATH_OPERATOR][E_M_NB_HEX] = m_number_analyzer;
}

t_ar_analyzer	*init_math_analyzer(void)
{
	static	t_ar_analyzer analyzer;

	bzero_analyzer(analyzer);
	init_m_start(analyzer);
	return (&analyzer);
}
