/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect_and_analyzer.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:15:21 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/02 19:16:46 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int				define_io_dup_move(t_token *token)
{
	int		len;
	int		index;

	len = ft_strlen(token->data);
	index = 0;
	if (len == 1 && token->data[0] == '-')
		return (A_CLOSE);
	while (index < len - 1)
	{
		if (ft_isdigit(token->data[index++]) == 0)
			return (A_AMBIGOUS_REDIRECT);
	}
	if (token->data[len - 1] == '-')
		return (A_MOVE);
	else if (ft_isdigit(token->data[len - 1]))
		return (A_DUP);
	else
		return (A_AMBIGOUS_REDIRECT);
}

void			io_and_redirect_flush(t_resolution *resolve)
{
	enum e_type type;
	t_list		*node;
	t_action	action;

	resolve->state = P_IO_FLUSH_AND;
	ft_bzero(&action, sizeof(t_action));
	node = ft_stckpopnode(&resolve->stack);
	if ((action.type = define_io_dup_move(node->data)) == A_AMBIGOUS_REDIRECT)
	{
		resolve->valid = -2;
		error_analyzer(resolve);
		return ;
	}
	ft_lstaddback(&action.data, node);
	node = ft_stckpopnode(&resolve->stack);
	type = ((t_token *)node->data)->type;
	ft_lstdelone(&node, NULL);
	node = ft_stckpopnode(&resolve->stack);
	if (type == E_GREATAND)
		ft_lstadd(&action.data, node);
	else if (type == E_LESSAND)
		ft_lstadd(&action.data, node);
	ft_stckpush(&resolve->tree_node, &action, sizeof(t_action));
}

void			io_redirect_and_analyzer(t_resolution *resolve)
{
	resolve->state = P_IO_REDIRECT_AND;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}
