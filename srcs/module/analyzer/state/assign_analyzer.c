/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 00:37:52 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/30 21:54:21 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	assign_flush_analyzer(t_resolution *resolve)
{
	t_list		*node;
	t_action	action;

	resolve->state = P_ASSIGN_FLUSH;
	ft_bzero(&action, sizeof(t_action));
	node = ft_stckpopnode(&resolve->stack);
	ft_lstadd(&action.data, node);
	node = ft_stckpopnode(&resolve->stack);
	ft_lstadd(&action.data, node);
	action.type = A_ASSIGN;
	ft_stckpush(&resolve->tree_node, &action, sizeof(t_action));
	resolve->valid = 1;
}

void	assign_data_analyzer(t_resolution *resolve)
{
	resolve->state = P_ASSIGN_DATA;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}

void	assign_name_analyzer(t_resolution *resolve)
{
	if (ft_isdigit(*resolve->token.data))
		resolve->state = P_STRING;
	else
		resolve->state = P_ASSIGN_NAME;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}
