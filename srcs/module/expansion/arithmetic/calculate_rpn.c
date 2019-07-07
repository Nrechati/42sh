/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_rpn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 11:57:30 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/07 19:28:06 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int8_t	check_forbidden_operation(t_rpn_tk *curr, t_rpn_tk *second)
{
	if (curr->value.type & (OPERATOR & DIVIDE)
			|| curr->value.type & (OPERATOR & MODULO))
	{
		if (second->value.digit == 0)
		{
			free(second);
			ft_dprintf(2, "42sh : Division by zero\n");
			return (FALSE);
		}
	}
	return (TRUE);
}

static int8_t	do_operation(t_rpn_tk *curr, t_stack *solve)
{
	t_rpn_tk	*second;
	t_list		*node;

	second = NULL;
	second = ft_stckpop(solve);
	node = ft_stckpopnode(solve);
	if (check_forbidden_operation(curr, second) == FALSE)
	{
		ft_lstdelone(&node, NULL);
		return (FAILURE);
	}
	do_math(node->data, second, curr);
	free(second);
	ft_stckpushnode(solve, node);
	return (SUCCESS);
}

static int8_t	handle_operator(t_rpn_tk *curr, t_stack *solve)
{
	t_list			*node;

	node = NULL;
	if (curr->value.type & (PRECEDENCE & UNARY_MINUS) && ft_stcksize(solve) > 0)
	{
		node = ft_stckpopnode(solve);
		do_unary(node->data, curr);
		ft_stckpushnode(solve, node);
	}
	else if (ft_stcksize(solve) < 2)
	{
		ft_dprintf(2, "Expression unsolvable\n");
		return (FAILURE);
	}
	else
	{
		if (do_operation(curr, solve) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int8_t	calcul(t_stack *rpn, t_stack *solve)
{
	t_list		*node;
	t_rpn_tk	*curr;

	node = ft_stckpopnode(rpn);
	curr = node->data;
	if (curr->type == RPN_NUMBER)
		ft_stckpushnode(solve, node);
	else if (curr->type == RPN_OPERATOR)
	{
		if (handle_operator(curr, solve) == FAILURE)
		{
			ft_lstdelone(&node, NULL);
			return (FAILURE);
		}
		ft_lstdelone(&node, NULL);
	}
	return (SUCCESS);
}

int8_t			calculate_rpn(t_stack *rpn, t_infix *infix)
{
	t_stack		solve;

	ft_stckinit(&solve);
	while (ft_stcksize(rpn) > 0)
	{
		if (calcul(rpn, &solve) == FAILURE)
		{
			ft_stckdestroy(&solve, NULL);
			ft_stckdestroy(&infix->calcul, NULL);
			return (FAILURE);
		}
	}
	if (ft_stcksize(&solve) != 1)
	{
		ft_dprintf(2, "Expression unsolvable\n");
		ft_stckdestroy(&solve, NULL);
		ft_stckdestroy(&infix->calcul, NULL);
		return (FAILURE);
	}
	infix->result = ((t_rpn_tk*)solve.head->data)->value.digit;
	ft_stckdestroy(&solve, NULL);
	return (SUCCESS);
}
