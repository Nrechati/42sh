/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:57:46 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/12 17:32:37 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>
#include <unistd.h>

void	flush_redirect_and(t_resolution *resolve)
{
	/*char			*filedesc;
	int				fd;
	unsigned int	action;
	t_type			type;
*/
	resolve->state = P_REDIRECT_FLUSH_AND;
	/*
	action = 0;
	filedesc = pop_token_data(&resolve->stack);
	fd = ft_atoi(filedesc);
	ft_strdel(&filedesc);
	type = pop_token_type(&resolve->stack);
	action |= resolve->special_case & TO_CLOSE ? FD_CLOSE : FD_DUP;
	resolve->special_case ^= TO_CLOSE;
	if (type == E_LESSAND)
		generate_filedesc(resolve, fd, STDIN_FILENO, action | FD_WRITE);
	else
		generate_filedesc(resolve, fd, STDOUT_FILENO, action | FD_WRITE);
		*/
}

enum e_actions	define_redirect(t_token *token)
{
	if (token->type == E_GREAT)
		return (A_STDOUT_TRUNCATE_FILE);
	if (token->type == E_DGREAT)
		return (A_STDOUT_APPEND_FILE);
	if (token->type == E_LESS)
		return (A_STDIN_READ_FILE);
	return (-1);
}

void	flush_redirect(t_resolution *resolve)
{
	t_token		*token;
	t_list		*node;
	t_action	action;

	resolve->state = P_REDIRECT_FLUSH;
	ft_bzero(&action, sizeof(t_action));
	node = ft_stckpopnode(&resolve->stack);
	ft_lstaddback(&action.data, node);
	node = ft_stckpopnode(&resolve->stack);
	token = node->data;
	action.type = define_redirect(token);
	ft_lstdelone(&node, NULL);
	node = ft_lstnew(&action, sizeof(t_action));
	ft_stckpush(&resolve->tree_node, &action, sizeof(t_action));
}

void	redirect_and_analyzer(t_resolution *resolve)
{
	resolve->state = P_REDIRECT_AND;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}

void	redirect_analyzer(t_resolution *resolve)
{
	resolve->state = P_REDIRECT;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}
