/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_rpn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 11:57:30 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/26 17:31:21 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void		do_the_math(t_rpn_tk *first, t_rpn_tk *second, t_rpn_tk *curr)
{
	if (curr->value.type & DIVIDE || curr->value.type & MODULO)
	{
		if (second->value.digit == 0)
		{
			ft_printf("Division by zero");
			return;
		}
	}
	if (curr->value.type & AND)
		first->value.digit = (first->value.digit && second->value.digit);
	else if (curr->value.type & OR)
		first->value.digit = (first->value.digit || second->value.digit);
	else if (curr->value.type & LESS)
		first->value.digit = (first->value.digit < second->value.digit);
	else if (curr->value.type & LESSEQ)
		first->value.digit = (first->value.digit <= second->value.digit);
	else if (curr->value.type & GREAT)
		first->value.digit = (first->value.digit > second->value.digit);
		else if (curr->value.type & GREATEQ)
		first->value.digit = (first->value.digit >= second->value.digit);
	else if (curr->value.type &EQUAL)
		first->value.digit = (first->value.digit == second->value.digit);
	else if (curr->value.type & DIFF)
		first->value.digit = (first->value.digit != second->value.digit);
	else if (curr->value.type & EQUAL)
		first->value.digit = (first->value.digit == second->value.digit);
	else if (curr->value.type & TIMES)
		first->value.digit *= second->value.digit;
	else if (curr->value.type & DIVIDE)
		first->value.digit /= second->value.digit;
	else if (curr->value.type & MODULO)
		first->value.digit %= second->value.digit;
	else if (curr->value.type & PLUS)
		first->value.digit += second->value.digit;
	else if (curr->value.type & MINUS)
		first->value.digit -= second->value.digit;
}

int64_t			calculate_rpn(t_stack *rpn)
{
	int64_t		result;
	t_stack		solve;
	t_rpn_tk	*second;
	t_rpn_tk	*first;
	t_rpn_tk	*curr;

	ft_stckinit(&solve);
	while (ft_stcksize(rpn) > 0)
	{
		first = NULL;
		second = NULL;
		curr = ft_stckpop(rpn);
		if (curr->type == RPN_NUMBER)
			ft_stckpush(&solve, curr, sizeof(t_rpn_tk));
		else if (curr->type == RPN_OPERATOR)
		{
			if (ft_stcksize(&solve) < 2)
			{
				ft_dprintf(2, "Expression unsolvable\n");
				return (FAILURE);
			}
			second = ft_stckpop(&solve);
			first = ft_stckpop(&solve);
			do_the_math(first, second, curr);
			ft_stckpush(&solve, first, sizeof(t_rpn_tk));
			//destroy second;
		}
		else
			ft_dprintf(2, "Wrong token in RPN stack\n");
	}
	if (ft_stcksize(&solve) != 1 )
	{
		ft_dprintf(2, "Expression unsolvable\n");
		return (FAILURE);
	}
	result = ((t_rpn_tk*)solve.head->data)->value.digit;
	return (result);
}
