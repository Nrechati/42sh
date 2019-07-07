/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:35:33 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/07 19:35:17 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		do_math(t_rpn_tk *first, t_rpn_tk *second, t_rpn_tk *curr)
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

uint8_t		is_left_p(t_stack *operator)
{
	t_rpn_tk	*top;

	if (ft_stcksize(operator) == 0)
		return (FALSE);
	top = ft_stcktop(operator);
	if (top->value.type & OPEN_P)
		return (TRUE);
	return (FALSE);
}

uint8_t		need_pop_operator(t_rpn_tk *curr, t_stack *operator)
{
	t_rpn_tk *top;

	if (ft_stcksize(operator) == 0)
		return (FALSE);
	top = ft_stcktop(operator);
	if (!(top->value.type & OPEN_P))
	{
		if ((curr->value.type & PRECEDENCE) <= (top->value.type & PRECEDENCE))
			return (TRUE);
		else
			return (FALSE);
	}
	return (FALSE);
}

int8_t		calculator(t_infix *infix)
{
	t_stack		rpn;

	ft_stckinit(&rpn);
	if (ft_stcksize(&infix->calcul) == 0)
		return (SUCCESS);
	if (ft_shunting_yds(&infix->calcul, &rpn) == FAILURE)
		return (FAILURE);
	ft_lstrev(&rpn.head);
	if (calculate_rpn(&rpn, infix) == FAILURE)
		return (FAILURE);
	ft_stckdestroy(&rpn, NULL);
	ft_stckdestroy(&infix->calcul, NULL);
	return (SUCCESS);
}
