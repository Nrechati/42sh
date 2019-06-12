/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:44:20 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/12 17:29:20 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_list	*generate_cmd_list(t_stack *tree_node)
{
	t_command	command;
	t_action	*action;
	t_list		*node;

	ft_bzero(&command, sizeof(t_command));
	action = ft_stckpop(tree_node);
	command.av = action->data;
	ft_free(&action);
	while (ft_stcksize(tree_node) > 0)
	{
		if (((t_action *)ft_stcktop(tree_node))->type == A_ARGS)
			break;
		node = ft_stckpopnode(tree_node);
		ft_lstadd(&command.actions, node);
	}
	node = ft_lstnew(&command, sizeof(t_command));
	return (node);
}

int8_t	generate_cmd_group(t_list **cmd_group, t_stack *tree_node)
{
	t_group 	group;
	t_action	*action;
	t_list		*node;
	t_list		*command_lst;

	command_lst = NULL;
	ft_bzero(&group, sizeof(t_group));
	action = ft_stckpop(tree_node);
	if (action->type == A_END)
		group.group_type |= GROUP_RUN;
	ft_free(&action);
	while (ft_stcksize(tree_node) > 0)
	{
		if ((node = generate_cmd_list(tree_node)) == NULL)
			return (FAILURE);
		ft_lstadd(&group.command_list, node);
	}
	node = ft_lstnew(&group, sizeof(t_list));
	ft_lstaddback(cmd_group, node);
	return (SUCCESS);
}

t_list	*analyzer(t_resolution *resolve)
{
	static t_analyzer	*analyzer = NULL;
	t_list				*cmd_group;

	cmd_group = NULL;
	if (analyzer == NULL)
		analyzer = init_analyzer();
	delete_analyzer(resolve);
//	reset_analyzer(g_shell, resolve);
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
			generate_cmd_group(&cmd_group, &resolve->tree_node);
		(*analyzer)[resolve->state][resolve->token.type](resolve);
	}
	analyzer_print_debug(g_shell, resolve);
	generate_cmd_group(&cmd_group, &resolve->tree_node);
	return	(cmd_group);
}
