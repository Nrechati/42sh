/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_calculator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:35:33 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/25 17:17:45 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

uint8_t		is_left_p(t_stack *operator)
{
	t_rpn_tk	*top;

	if (ft_stcksize(operator) == 0)
		return (FALSE);
	top = ft_stcktop(operator);
	if (top->value.type & LEFT_P)
		return (TRUE);
	return (FALSE);
}

uint8_t		need_pop_operator(t_rpn_tk *curr, t_stack *operator)
{
	t_rpn_tk 	*top;

	if (ft_stcksize(operator) == 0)
		return (FALSE);
	top = ft_stcktop(operator);
	if (!(top->value.type & LEFT_P))
	{
		if (curr->value.type & LOW && top->value.type & HIGH)
			return (TRUE);
		if (curr->value.type & LOW && top->value.type & LOW)
			return (TRUE);
		if (curr->value.type & HIGH && top->value.type & HIGH)
			return (TRUE);
	}
	return (FALSE);
}

int8_t			arithmetic_calculator(t_infix *infix)
{
	t_stack		rpn;

	ft_stckinit(&rpn);
	if (ft_shunting_yds(&infix->calcul, &rpn) == FAILURE)
		return (FAILURE);
	ft_lstrev(&rpn.head);
	infix->result = calculate_rpn(&rpn);
	//free rpn stack;
	//free infix stack;
	return (SUCCESS);
}
