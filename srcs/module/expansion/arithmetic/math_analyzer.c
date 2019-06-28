/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_analyzer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nrechati <Nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:31:55 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/28 17:55:15 by Nrechati         ###   ########.fr       */
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
	analyzer[MATH_START][E_M_PLUS] = m_unary_analyzer;
	analyzer[MATH_START][E_M_MINUS] = m_unary_analyzer;
	analyzer[MATH_START][E_M_NB_DEC] = m_number_analyzer;
	analyzer[MATH_START][E_M_NB_OCT] = m_number_analyzer;
	analyzer[MATH_START][E_M_NB_HEX] = m_number_analyzer;
	analyzer[MATH_START][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_START][E_M_STRING] = m_variable_analyzer;
	analyzer[MATH_START][E_M_DPLUS] = m_preffix;
	analyzer[MATH_START][E_M_DMINUS] = m_preffix;
	analyzer[MATH_START][E_M_END] = m_end_analyzer;
}

void 		init_m_number(t_ar_analyzer analyzer)
{
	analyzer[MATH_NUMBER][E_M_PLUS] = m_operator_analyzer;
	analyzer[MATH_NUMBER][E_M_MINUS] = m_operator_analyzer;
	analyzer[MATH_NUMBER][E_M_TIMES] = m_operator_analyzer;
	analyzer[MATH_NUMBER][E_M_MODULO] = m_operator_analyzer;
	analyzer[MATH_NUMBER][E_M_DIVIDE] = m_operator_analyzer;
	analyzer[MATH_NUMBER][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_NUMBER][E_M_CLOSEP] = m_parenthesis_analyzer;
	analyzer[MATH_NUMBER][E_M_LESS] = m_logical_operator;
	analyzer[MATH_NUMBER][E_M_GREAT] = m_logical_operator;
	analyzer[MATH_NUMBER][E_M_LESSEQ] = m_logical_operator;
	analyzer[MATH_NUMBER][E_M_GREATEQ] = m_logical_operator;
	analyzer[MATH_NUMBER][E_M_EQUAL] = m_logical_operator;
	analyzer[MATH_NUMBER][E_M_NEQUAL] = m_logical_operator;
	analyzer[MATH_NUMBER][E_M_AND] = m_logical_operator;
	analyzer[MATH_NUMBER][E_M_OR] = m_logical_operator;
	analyzer[MATH_NUMBER][E_M_END] = m_end_analyzer;
}

void		init_m_unary(t_ar_analyzer analyzer)
{
	analyzer[MATH_UNARY][E_M_NB_DEC] = m_number_analyzer;
	analyzer[MATH_UNARY][E_M_NB_OCT] = m_number_analyzer;
	analyzer[MATH_UNARY][E_M_NB_HEX] = m_number_analyzer;
	analyzer[MATH_UNARY][E_M_PLUS] = m_unary_analyzer;
	analyzer[MATH_UNARY][E_M_MINUS] = m_unary_analyzer;;
	analyzer[MATH_UNARY][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_UNARY][E_M_DPLUS] = m_preffix;
	analyzer[MATH_UNARY][E_M_DMINUS] = m_preffix;
}

void 		init_m_operator(t_ar_analyzer analyzer)
{
	analyzer[MATH_OPERATOR][E_M_NB_DEC] = m_number_analyzer;
	analyzer[MATH_OPERATOR][E_M_NB_OCT] = m_number_analyzer;
	analyzer[MATH_OPERATOR][E_M_NB_HEX] = m_number_analyzer;
	analyzer[MATH_OPERATOR][E_M_STRING] = m_variable_analyzer;
	analyzer[MATH_OPERATOR][E_M_PLUS] = m_unary_analyzer;
	analyzer[MATH_OPERATOR][E_M_MINUS] = m_unary_analyzer;
	analyzer[MATH_OPERATOR][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_OPERATOR][E_M_CLOSEP] = m_parenthesis_analyzer;
	analyzer[MATH_OPERATOR][E_M_DPLUS] = m_preffix;
	analyzer[MATH_OPERATOR][E_M_DMINUS] = m_preffix;
}

void		init_m_preffix(t_ar_analyzer analyzer)
{
	analyzer[MATH_PREFFIX][E_M_PLUS] = m_operator_analyzer;
	analyzer[MATH_PREFFIX][E_M_MINUS] = m_operator_analyzer;
	analyzer[MATH_PREFFIX][E_M_TIMES] = m_operator_analyzer;
	analyzer[MATH_PREFFIX][E_M_MODULO] = m_operator_analyzer;
	analyzer[MATH_PREFFIX][E_M_DIVIDE] = m_operator_analyzer;
	analyzer[MATH_PREFFIX][E_M_LESS] = m_logical_operator;
	analyzer[MATH_PREFFIX][E_M_GREAT] = m_logical_operator;
	analyzer[MATH_PREFFIX][E_M_LESSEQ] = m_logical_operator;
	analyzer[MATH_PREFFIX][E_M_GREATEQ] = m_logical_operator;
	analyzer[MATH_PREFFIX][E_M_EQUAL] = m_logical_operator;
	analyzer[MATH_PREFFIX][E_M_NEQUAL] = m_logical_operator;
	analyzer[MATH_PREFFIX][E_M_AND] = m_logical_operator;
	analyzer[MATH_PREFFIX][E_M_OR] = m_logical_operator;
	analyzer[MATH_PREFFIX][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_PREFFIX][E_M_CLOSEP] = m_parenthesis_analyzer;
	analyzer[MATH_PREFFIX][E_M_END] = m_end_analyzer;
}

void		init_m_suffix(t_ar_analyzer analyzer)
{
	analyzer[MATH_SUFFIX][E_M_PLUS] = m_operator_analyzer;
	analyzer[MATH_SUFFIX][E_M_MINUS] = m_operator_analyzer;
	analyzer[MATH_SUFFIX][E_M_TIMES] = m_operator_analyzer;
	analyzer[MATH_SUFFIX][E_M_MODULO] = m_operator_analyzer;
	analyzer[MATH_SUFFIX][E_M_DIVIDE] = m_operator_analyzer;
	analyzer[MATH_SUFFIX][E_M_LESS] = m_logical_operator;
	analyzer[MATH_SUFFIX][E_M_GREAT] = m_logical_operator;
	analyzer[MATH_SUFFIX][E_M_LESSEQ] = m_logical_operator;
	analyzer[MATH_SUFFIX][E_M_GREATEQ] = m_logical_operator;
	analyzer[MATH_SUFFIX][E_M_EQUAL] = m_logical_operator;
	analyzer[MATH_SUFFIX][E_M_NEQUAL] = m_logical_operator;
	analyzer[MATH_SUFFIX][E_M_AND] = m_logical_operator;
	analyzer[MATH_SUFFIX][E_M_OR] = m_logical_operator;
	analyzer[MATH_SUFFIX][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_SUFFIX][E_M_CLOSEP] = m_parenthesis_analyzer;
	analyzer[MATH_SUFFIX][E_M_END] = m_end_analyzer;
}

void		init_m_variable(t_ar_analyzer analyzer)
{
	analyzer[MATH_VARIABLE][E_M_PLUS] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_MINUS] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_TIMES] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_MODULO] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_DIVIDE] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_LESS] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_GREAT] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_LESSEQ] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_GREATEQ] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_EQUAL] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_NEQUAL] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_AND] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_OR] = m_flush_variable_analyzer;
	analyzer[MATH_VARIABLE][E_M_DPLUS] = m_suffix;
	analyzer[MATH_VARIABLE][E_M_DMINUS] = m_suffix;
	analyzer[MATH_VARIABLE][E_M_END] = m_flush_variable_analyzer;
}

void		init_m_flush_variable(t_ar_analyzer analyzer)
{
	analyzer[MATH_VARIABLE_FLUSH][E_M_PLUS] = m_operator_analyzer;
	analyzer[MATH_VARIABLE_FLUSH][E_M_MINUS] = m_operator_analyzer;
	analyzer[MATH_VARIABLE_FLUSH][E_M_TIMES] = m_operator_analyzer;
	analyzer[MATH_VARIABLE_FLUSH][E_M_MODULO] = m_operator_analyzer;
	analyzer[MATH_VARIABLE_FLUSH][E_M_DIVIDE] = m_operator_analyzer;
	analyzer[MATH_VARIABLE_FLUSH][E_M_LESS] = m_logical_operator;
	analyzer[MATH_VARIABLE_FLUSH][E_M_GREAT] = m_logical_operator;
	analyzer[MATH_VARIABLE_FLUSH][E_M_LESSEQ] = m_logical_operator;
	analyzer[MATH_VARIABLE_FLUSH][E_M_GREATEQ] = m_logical_operator;
	analyzer[MATH_VARIABLE_FLUSH][E_M_EQUAL] = m_logical_operator;
	analyzer[MATH_VARIABLE_FLUSH][E_M_NEQUAL] = m_logical_operator;
	analyzer[MATH_VARIABLE_FLUSH][E_M_AND] = m_logical_operator;
	analyzer[MATH_VARIABLE_FLUSH][E_M_OR] = m_logical_operator;
	analyzer[MATH_VARIABLE_FLUSH][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_VARIABLE_FLUSH][E_M_CLOSEP] = m_parenthesis_analyzer;
	analyzer[MATH_VARIABLE_FLUSH][E_M_END] = m_end_analyzer;
}

void		init_m_open_parent(t_ar_analyzer analyzer)
{
	analyzer[MATH_OPEN_PARENT][E_M_PLUS] = m_unary_analyzer;
	analyzer[MATH_OPEN_PARENT][E_M_MINUS] = m_unary_analyzer;
	analyzer[MATH_OPEN_PARENT][E_M_NB_DEC] = m_number_analyzer;
	analyzer[MATH_OPEN_PARENT][E_M_NB_OCT] = m_number_analyzer;
	analyzer[MATH_OPEN_PARENT][E_M_NB_HEX] = m_number_analyzer;
	analyzer[MATH_OPEN_PARENT][E_M_STRING] = m_variable_analyzer;
	analyzer[MATH_OPEN_PARENT][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_OPEN_PARENT][E_M_CLOSEP] = m_parenthesis_analyzer;
	analyzer[MATH_OPEN_PARENT][E_M_DPLUS] = m_preffix;
	analyzer[MATH_OPEN_PARENT][E_M_DMINUS] = m_preffix;
}

void		init_m_close_parent(t_ar_analyzer analyzer)
{
	analyzer[MATH_CLOSE_PARENT][E_M_PLUS] = m_operator_analyzer;
	analyzer[MATH_CLOSE_PARENT][E_M_MINUS] = m_operator_analyzer;
	analyzer[MATH_CLOSE_PARENT][E_M_TIMES] = m_operator_analyzer;
	analyzer[MATH_CLOSE_PARENT][E_M_MODULO] = m_operator_analyzer;
	analyzer[MATH_CLOSE_PARENT][E_M_DIVIDE] = m_operator_analyzer;
	analyzer[MATH_CLOSE_PARENT][E_M_LESS] = m_logical_operator;
	analyzer[MATH_CLOSE_PARENT][E_M_GREAT] = m_logical_operator;
	analyzer[MATH_CLOSE_PARENT][E_M_LESSEQ] = m_logical_operator;
	analyzer[MATH_CLOSE_PARENT][E_M_GREATEQ] = m_logical_operator;
	analyzer[MATH_CLOSE_PARENT][E_M_EQUAL] = m_logical_operator;
	analyzer[MATH_CLOSE_PARENT][E_M_NEQUAL] = m_logical_operator;
	analyzer[MATH_CLOSE_PARENT][E_M_AND] = m_logical_operator;
	analyzer[MATH_CLOSE_PARENT][E_M_OR] = m_logical_operator;
	analyzer[MATH_CLOSE_PARENT][E_M_OPENP] = m_parenthesis_analyzer;
	analyzer[MATH_CLOSE_PARENT][E_M_CLOSEP] = m_parenthesis_analyzer;
	analyzer[MATH_CLOSE_PARENT][E_M_END] = m_end_analyzer;
}

void		init_m_logical_operator(t_ar_analyzer analyzer)
{
	analyzer[MATH_LOGICAL_OPERATOR][E_M_NB_DEC] = m_number_analyzer;
	analyzer[MATH_LOGICAL_OPERATOR][E_M_NB_OCT] = m_number_analyzer;
	analyzer[MATH_LOGICAL_OPERATOR][E_M_NB_HEX] = m_number_analyzer;
	analyzer[MATH_LOGICAL_OPERATOR][E_M_PLUS] = m_unary_analyzer;
	analyzer[MATH_LOGICAL_OPERATOR][E_M_MINUS] = m_unary_analyzer;
	analyzer[MATH_LOGICAL_OPERATOR][E_M_DPLUS] = m_preffix;
	analyzer[MATH_LOGICAL_OPERATOR][E_M_DMINUS] = m_preffix;
}

t_ar_analyzer	*init_math_analyzer(void)
{
	static	t_ar_analyzer analyzer;

	bzero_analyzer(analyzer);
	init_m_start(analyzer);
	init_m_number(analyzer);
	init_m_unary(analyzer);
	init_m_operator(analyzer);
	init_m_logical_operator(analyzer);
	init_m_preffix(analyzer);
	init_m_suffix(analyzer);
	init_m_open_parent(analyzer);
	init_m_close_parent(analyzer);
	init_m_start(analyzer);
	init_m_variable(analyzer);
	init_m_flush_variable(analyzer);
	return (&analyzer);
}
