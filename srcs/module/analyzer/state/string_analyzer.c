/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 21:17:49 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/30 08:44:47 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	flush_string(t_resolution *resolve)
{
	t_list		*node;
	t_action	action;

	node = NULL;
	resolve->state = P_STRING_FLUSH;
	ft_bzero(&action, sizeof(t_action));
	action.type = A_ARGS;
	resolve->valid = 1;
	while (ft_stcksize(&resolve->stack) != 0)
	{
		node = ft_stckpopnode(&resolve->stack);
		ft_lstadd(&action.data, node);
	}
	ft_stckpush(&resolve->tree_node, &action, sizeof(t_action));
	return ;
}

void	string_analyzer(t_resolution *resolve)
{
	resolve->state = P_STRING;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}
