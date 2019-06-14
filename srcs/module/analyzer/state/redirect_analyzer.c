/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:57:46 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/13 00:33:49 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>
#include <unistd.h>

void	dup_stderr(t_resolution *resolve)
{
	t_action	action;
	t_token		token;
	t_list		*node;

	ft_bzero(&action, sizeof(t_action));
	action.type = A_DUP;
	token.type = E_IO_NUMBER;
	token.data = ft_strdup("1");
	node = ft_lstnew(&token, sizeof(t_token));
	ft_lstadd(&action.data, node);
	token.data = ft_strdup("2");
	node = ft_lstnew(&token, sizeof(t_token));
	ft_lstaddback(&action.data, node);
	node = ft_lstnew(&token, sizeof(t_action));
	ft_stckpush(&resolve->tree_node, &action, sizeof(t_action));
}

enum e_actions	define_redirect(t_token *token)
{
	if (token->type == E_GREAT || token->type == E_ANDGREAT
			|| token->type == E_GREATAND)
		return (A_STDOUT_TRUNCATE_FILE);
	if (token->type == E_DGREAT || token->type == E_ANDDGREAT)
		return (A_STDOUT_APPEND_FILE);
	if (token->type == E_LESS)
		return (A_STDIN_READ_FILE);
	return (-1);
}

void			flush_redirect(t_resolution *resolve)
{
	enum e_type	type;
	t_list		*node;
	t_action	action;

	resolve->state = P_REDIRECT_FLUSH;
	ft_bzero(&action, sizeof(t_action));
	node = ft_stckpopnode(&resolve->stack);
	ft_lstaddback(&action.data, node);
	node = ft_stckpopnode(&resolve->stack);
	action.type = define_redirect(node->data);
	type = ((t_token *)node->data)->type;
	ft_lstdelone(&node, NULL);
	node = ft_lstnew(&action, sizeof(t_action));
	ft_stckpush(&resolve->tree_node, &action, sizeof(t_action));
	if (type == E_ANDGREAT || type == E_ANDDGREAT || type == E_GREATAND)
		dup_stderr(resolve);
}

void			redirect_and_analyzer(t_resolution *resolve)
{
	resolve->state = P_REDIRECT_AND;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}

void			redirect_analyzer(t_resolution *resolve)
{
	resolve->state = P_REDIRECT;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}
