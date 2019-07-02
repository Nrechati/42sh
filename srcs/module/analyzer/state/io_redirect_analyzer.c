/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect_analyzer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 04:42:30 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/02 19:15:44 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

enum e_actions	define_io_redirect(t_token *token)
{
	if (token->type == E_GREAT)
		return (A_IO_TRUNCATE_FILE);
	if (token->type == E_DGREAT)
		return (A_IO_APPEND_FILE);
	if (token->type == E_LESS)
		return (A_IO_READ_FILE);
	return (-1);
}

void			io_redirect_flush(t_resolution *resolve)
{
	t_token		*token;
	t_list		*node;
	t_action	action;

	resolve->state = P_IO_FLUSH;
	ft_bzero(&action, sizeof(t_action));
	node = ft_stckpopnode(&resolve->stack);
	ft_lstaddback(&action.data, node);
	node = ft_stckpopnode(&resolve->stack);
	token = node->data;
	action.type = define_io_redirect(token);
	ft_lstdelone(&node, NULL);
	node = ft_stckpopnode(&resolve->stack);
	ft_lstaddback(&action.data, node);
	ft_stckpush(&resolve->tree_node, &action, sizeof(t_action));
}

void			io_redirect_analyzer(t_resolution *resolve)
{
	if (resolve->token.type == E_DLESS || resolve->token.type == E_DLESSDASH)
		resolve->state = P_IO_HEREDOC_REDIRECT;
	else
		resolve->state = P_IO_REDIRECT;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}

void			io_analyzer(t_resolution *resolve)
{
	resolve->state = P_IO;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}
