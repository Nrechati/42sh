/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 22:43:18 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/26 01:10:14 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		del_infix(t_infix *infix)
{
	ft_stckdestroy(&infix->calcul, NULL);
}

void		m_get_token(t_arithmetic *arithmetic, t_list **node)
{
	if (node)
		ft_lstdel(node, NULL);
	arithmetic->current = arithmetic->tokens;
	arithmetic->tokens = arithmetic->tokens->next;
	arithmetic->current->next = NULL;
	arithmetic->curr_token = arithmetic->current->data;
}
