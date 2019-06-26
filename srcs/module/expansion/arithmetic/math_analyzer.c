/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_analyzer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:31:55 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/26 01:00:19 by cempassi         ###   ########.fr       */
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

void 		init_m_start(t_ar_analyzer analyzer)
{
	analyzer[MATH_START][E_M_PLUS] = m_preffix_plus_minus_analyzer;
	analyzer[MATH_START][E_M_MINUS] = m_preffix_plus_minus_analyzer;
	analyzer[MATH_START][E_M_NB_DEC] = m_number_analyzer;
	analyzer[MATH_START][E_M_NB_OCT] = m_number_analyzer;
	analyzer[MATH_START][E_M_NB_HEX] = m_number_analyzer;
	analyzer[MATH_START][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_START][E_M_STRING] = m_variable_analyzer;
}

void 		init_m_number(t_ar_analyzer analyzer)
{
	analyzer[MATH_NUMBER][E_M_PLUS] = m_plus_minus_analyzer;
	analyzer[MATH_NUMBER][E_M_MINUS] = m_plus_minus_analyzer;
	analyzer[MATH_NUMBER][E_M_TIMES] = m_operator_analyzer;
	analyzer[MATH_NUMBER][E_M_MODULO] = m_operator_analyzer;
	analyzer[MATH_NUMBER][E_M_DIVIDE] = m_operator_analyzer;
	analyzer[MATH_NUMBER][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_NUMBER][E_M_CLOSEP] = m_parenthesis_analyzer;
	analyzer[MATH_NUMBER][E_M_END] = m_end_analyzer;
}

void 		init_m_operator(t_ar_analyzer analyzer)
{
	analyzer[MATH_OPERATOR][E_M_NB_DEC] = m_number_analyzer;
	analyzer[MATH_OPERATOR][E_M_NB_OCT] = m_number_analyzer;
	analyzer[MATH_OPERATOR][E_M_NB_HEX] = m_number_analyzer;
}

void		init_m_close_parent(t_ar_analyzer analyzer)
{
	analyzer[MATH_CLOSE_PARENT][E_M_PLUS] = m_plus_minus_analyzer;
	analyzer[MATH_CLOSE_PARENT][E_M_MINUS] = m_plus_minus_analyzer;
	analyzer[MATH_CLOSE_PARENT][E_M_TIMES] = m_operator_analyzer;
	analyzer[MATH_CLOSE_PARENT][E_M_MODULO] = m_operator_analyzer;
	analyzer[MATH_CLOSE_PARENT][E_M_DIVIDE] = m_operator_analyzer;
	analyzer[MATH_CLOSE_PARENT][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_CLOSE_PARENT][E_M_CLOSEP] = m_parenthesis_analyzer;
}

void		init_m_stop(t_ar_analyzer analyzer)
{
	analyzer[MATH_STOP][E_M_PLUS] = m_preffix_plus_minus_analyzer;
	analyzer[MATH_STOP][E_M_MINUS] = m_preffix_plus_minus_analyzer;
	analyzer[MATH_STOP][E_M_NB_DEC] = m_number_analyzer;
	analyzer[MATH_STOP][E_M_NB_OCT] = m_number_analyzer;
	analyzer[MATH_STOP][E_M_NB_HEX] = m_number_analyzer;
	analyzer[MATH_STOP][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_STOP][E_M_STRING] = m_variable_analyzer;
}

void		init_m_preffix_plus(t_ar_analyzer analyzer)
{
	analyzer[MATH_PREFIX_PLUS][E_M_PLUS] = m_preffix_plus_minus_analyzer;
	analyzer[MATH_PREFIX_PLUS][E_M_DELIMITER] = m_flush_preffix_sign_analyzer;
}

void		init_m_flush_preffixed_sign(t_ar_analyzer analyzer)
{
	analyzer[MATH_FLUSH_PREFFIX_SIGN][E_M_NB_DEC] = m_preffixed_number_analyzer;
	analyzer[MATH_FLUSH_PREFFIX_SIGN][E_M_NB_OCT] = m_preffixed_number_analyzer;
	analyzer[MATH_FLUSH_PREFFIX_SIGN][E_M_NB_HEX] = m_preffixed_number_analyzer;
}

void		init_m_preffixed_number(t_ar_analyzer analyzer)
{
	analyzer[MATH_PREFFIXED_NUMBER][E_M_PLUS] = m_plus_minus_analyzer;
	analyzer[MATH_PREFFIXED_NUMBER][E_M_MINUS] = m_plus_minus_analyzer;
	analyzer[MATH_PREFFIXED_NUMBER][E_M_TIMES] = m_operator_analyzer;
	analyzer[MATH_PREFFIXED_NUMBER][E_M_MODULO] = m_operator_analyzer;
	analyzer[MATH_PREFFIXED_NUMBER][E_M_DIVIDE] = m_operator_analyzer;
	analyzer[MATH_PREFFIXED_NUMBER][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_PREFFIXED_NUMBER][E_M_CLOSEP] = m_parenthesis_analyzer;
	analyzer[MATH_PREFFIXED_NUMBER][E_M_END] = m_end_analyzer;
}

void		init_m_plus(t_ar_analyzer analyzer)
{
	analyzer[MATH_PLUS][E_M_DELIMITER] = m_flush_sign_analyzer;
}

void		init_m_minus(t_ar_analyzer analyzer)
{
	analyzer[MATH_MINUS][E_M_DELIMITER] = m_flush_sign_analyzer;
}

void		init_m_flush_sign(t_ar_analyzer analyzer)
{
	analyzer[MATH_FLUSH_SIGN][E_M_NB_DEC] = m_number_analyzer;
	analyzer[MATH_FLUSH_SIGN][E_M_NB_OCT] = m_number_analyzer;
	analyzer[MATH_FLUSH_SIGN][E_M_NB_HEX] = m_number_analyzer;
}

t_ar_analyzer	*init_math_analyzer(void)
{
	static	t_ar_analyzer analyzer;

	bzero_analyzer(analyzer);
	init_m_start(analyzer);
	init_m_number(analyzer);
	init_m_operator(analyzer);
	init_m_close_parent(analyzer);
	init_m_start(analyzer);
	init_m_preffix_plus(analyzer);
	//init_m_preffix_minus(analyzer);
	init_m_flush_sign(analyzer);
	init_m_flush_preffixed_sign(analyzer);
	init_m_preffixed_number(analyzer);
	init_m_plus(analyzer);
	init_m_minus(analyzer);
	return (&analyzer);
}
