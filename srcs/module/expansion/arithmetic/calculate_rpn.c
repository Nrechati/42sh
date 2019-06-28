/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_rpn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nrechati <Nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 11:57:30 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/28 19:10:11 by Nrechati         ###   ########.fr       */
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

static int8_t	check_forbidden_operation(t_rpn_tk *curr, t_rpn_tk *second)
{
	if (curr->value.type & (OPERATOR & DIVIDE)
			|| curr->value.type & (OPERATOR & MODULO))
		if (second->value.digit == 0)
		{
			ft_dprintf(2, "Division by zero\n");
			return (FALSE);
		}
	return (TRUE);
}

static int8_t	handle_operator(t_rpn_tk *curr, t_stack *solve)
{
	t_rpn_tk		*first;
	t_rpn_tk		*second;

	first = NULL;
	second = NULL;
	if (curr->value.type & (PRECEDENCE & UNARY_MINUS) && ft_stcksize(solve) > 0)
	{
		first = ft_stckpop(solve);
		do_unary(first, curr);
	}
	else if (ft_stcksize(solve) < 2)
	{
		ft_dprintf(2, "Expression unsolvable\n");
		return (FAILURE);
	}
	else
	{
		second = ft_stckpop(solve);
		first = ft_stckpop(solve);
		if (check_forbidden_operation(curr, second) == FALSE)
			return (FAILURE);
		do_math(first, second, curr);
	}
	ft_stckpush(solve, first, sizeof(t_rpn_tk));
	return (SUCCESS);
}

int8_t			calculate_rpn(t_stack *rpn, t_infix  *infix)
{
	t_stack		solve;
	t_rpn_tk	*curr;

	ft_stckinit(&solve);
	while (ft_stcksize(rpn) > 0)
	{
		curr = ft_stckpop(rpn);
		if (curr->type == RPN_NUMBER)
			ft_stckpush(&solve, curr, sizeof(t_rpn_tk));
		else if (curr->type == RPN_OPERATOR)
		{
			if (handle_operator(curr, &solve) == FAILURE)
				return (FAILURE);
		}
	}
	if (ft_stcksize(&solve) != 1)
	{
		ft_dprintf(2, "Expression unsolvable\n");
		return (FAILURE);
	}
	infix->result = ((t_rpn_tk*)solve.head->data)->value.digit;
	return (SUCCESS);
}
