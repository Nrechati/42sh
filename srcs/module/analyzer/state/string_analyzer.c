/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 21:17:49 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/13 01:49:21 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	flush_string(t_resolution *resolve)
{
	t_token		*token;
	t_list		*new_node;
	t_action	action;

	new_node = NULL;
	resolve->state = P_STRING_FLUSH;
	ft_bzero(&action, sizeof(t_action));
	action.type = A_ARGS;
	while (ft_stcksize(&resolve->stack) != 0)
	{
		token = ft_stckpop(&resolve->stack);
		new_node = ft_lstnew(token, sizeof(t_token));
		ft_lstadd(&action.data, new_node);
	}
	ft_stckpush(&resolve->tree_node, &action, sizeof(t_action));
	resolve->valid = 1;
	return ;
}

void	special_string_analyzer(t_resolution *resolve)
{
	resolve->state = P_SPSTRING;
	resolve->token.type = E_STRING;
	get_token(resolve);
}

void	string_analyzer(t_resolution *resolve)
{
	resolve->state = P_STRING;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}

