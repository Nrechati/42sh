/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:38:19 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/26 22:58:18 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int8_t	close_bracket(t_rpn_tk *curr, t_stack *operator, t_stack *rpn)
{
	while (is_left_p(operator) == FALSE)
		if (ft_stckpush(rpn, ft_stckpop(operator)
				, sizeof(t_rpn_tk)) == FAILURE)
			return (FAILURE);
	if (is_left_p(operator) == TRUE)
		curr = ft_stckpop(operator);
	return (SUCCESS);
}

static int8_t	handle_operator(t_rpn_tk *curr, t_stack *operator, t_stack *rpn)
{
	while (need_pop_operator(curr, operator) == TRUE)
		if (ft_stckpush(rpn, ft_stckpop(operator), sizeof(t_rpn_tk)) == FAILURE)
			return (FAILURE);
	if (ft_stckpush(operator, curr, sizeof(t_rpn_tk)) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int8_t	handle_bracket(t_rpn_tk *curr, t_stack *operator, t_stack *rpn)
{
	if (curr->value.type == OPEN_P)
	{
		if (ft_stckpush(operator, curr, sizeof(t_rpn_tk)) == FAILURE)
			return (FAILURE);
	}
	else if (close_bracket(curr, operator, rpn) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int8_t			ft_shunting_yds(t_stack *infix, t_stack *rpn)
{
	t_rpn_tk	*curr;
	t_stack		operator;

	ft_stckinit(&operator);
	while (ft_stcksize(infix) > 0)
	{
		curr = ft_stckpop(infix);
		if (curr->type == RPN_NUMBER)
		{
			if (ft_stckpush(rpn, curr, sizeof(t_rpn_tk)) == FAILURE)
				return (FAILURE);
		}
		else if (curr->type == RPN_OPERATOR)
		{
			if (handle_operator(curr, &operator, rpn) == FAILURE)
				return (FAILURE);
		}
		else if (curr->type == RPN_PARENT_OPEN || curr->type == RPN_PARENT_CLOSE)
		{
			if (handle_bracket(curr, &operator, rpn) == FAILURE)
				return (FAILURE);
		}
	}
	while (ft_stcksize(&operator) > 0)
		if (ft_stckpush(rpn, ft_stckpop(&operator), sizeof(t_rpn_tk)) == FAILURE)
			return (FAILURE);
	//free operator stack;
	return (SUCCESS);
}
