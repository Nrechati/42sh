/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:44:20 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/05 15:40:19 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	*pop_token_data(t_stack *stack)
{
	t_token *token;
	char	*data;

	token = ft_stckpop(stack);
	data = token->data;
	ft_free(token);
	return (data);
}

t_type	pop_token_type(t_stack *stack)
{
	t_token		*token;
	t_type		type;

	token = ft_stckpop(stack);
	type = token->type;
	ft_free(token);
	return (type);
}

void	generate_filedesc(t_resolution *resolve, int first, int second,
				int action)
{
	t_list		*node;
	t_filedesc	fd;

	fd.action = action;
	fd.first = first;
	fd.second = second;
	node = ft_lstnew(&fd, sizeof(t_filedesc));
	if (action & FD_PIPE)
		ft_lstadd(&resolve->process.fd, node);
	else
		ft_lstaddback(&resolve->process.fd, node);
}

void	get_token(t_resolution *resolve)
{
	t_list		*node;

	if (resolve->token_list == NULL)
		return ;
	node = resolve->token_list;
	resolve->token_list = resolve->token_list->next;
	ft_memcpy(&resolve->token, node->data, sizeof(t_token));
	ft_lstdelone(&node, NULL);
}

int8_t	generate_cmd_group(t_list **cmd_group, t_stack *tree_node)
{
	TOUT
}

t_list	*analyzer(t_resolution *resolve)
{
	static t_analyzer	*analyzer = NULL;
	t_list				*cmd_group;

	cmd_group = NULL;
	if (analyzer == NULL)
		analyzer = init_analyzer();
	delete_analyzer(resolve);
	reset_analyzer(g_shell, resolve);
	if (resolve->token.type == E_DEFAULT)
		get_token(resolve);
	if (resolve->state == P_STOP)
		resolve->state = P_START;
	while (resolve->state != P_END && resolve->state != P_ERROR)
	{
		if (g_shell->analyzer_signal == TRUE)
		{
			signal_analyzer(resolve);
			break ;
		}
		if (resolve->state == P_STOP)
			break ;
		(*analyzer)[resolve->state][resolve->token.type](resolve);
	}
	analyzer_print_debug(g_shell, resolve);
	generate_cmd_group(&cmd_group, &resolve->tree_node);
	return	(cmd_group);
}
