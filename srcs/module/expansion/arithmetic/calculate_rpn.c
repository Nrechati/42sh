/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_rpn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 11:57:30 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/27 14:46:48 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void		do_math(t_rpn_tk *first, t_rpn_tk *second, t_rpn_tk *curr)
{
	if (curr->value.type & (PRECEDENCE & AND))
		do_logical(first, second, curr);
	else if (curr->value.type & (PRECEDENCE & EQUAL))
		do_compare(first, second, curr);
	else if (curr->value.type & (PRECEDENCE & TIMES))
		do_high_op(first, second, curr);
	else if (curr->value.type & (PRECEDENCE & PLUS))
		do_low_op(first, second, curr);
}

static int8_t 	handle_operator(t_rpn_tk *curr, t_stack *solve)
{
	t_rpn_tk		*first;
	t_rpn_tk		*second;

	first = NULL;
	second = NULL;
	if (ft_stcksize(solve) < 2)
	{
		if ((curr->value.type & OPERATOR) == UNARY_MINUS
				|| (curr->value.type & OPERATOR) == UNARY_PLUS)
		{
			ft_dprintf(2, "Expression unsolvable\n");
			return (FAILURE);
		}
		first = ft_stckpop(solve);
		do_unary(first, curr);
	}
	else
	{
		second = ft_stckpop(solve);
		first = ft_stckpop(solve);
		do_math(first, second, curr);
	}
	ft_stckpush(solve, first, sizeof(t_rpn_tk));
	//destroy second;
	return (SUCCESS);
}

int64_t			calculate_rpn(t_stack *rpn)
{
	int64_t		result;
	t_stack		solve;
	t_rpn_tk	*curr;

	ft_stckinit(&solve);
	while (ft_stcksize(rpn) > 0)
	{
		curr = ft_stckpop(rpn);
		if (curr->type == RPN_NUMBER)
			ft_stckpush(&solve, curr, sizeof(t_rpn_tk));
		else if (curr->type == RPN_OPERATOR)
			handle_operator(curr, &solve);
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
