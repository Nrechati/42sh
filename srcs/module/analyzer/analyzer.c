/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:44:20 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/14 01:09:12 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	command_assign(t_stack *tree_node, t_command *command)
{
	t_list		*node;


	command->type |= COMMAND_ASSIGN;
	while (ft_stcksize(tree_node) > 0)
	{
		node = ft_stckpopnode(tree_node);
		ft_lstadd(&command->av, node);
	}
}

void	command_args(t_stack *tree_node, t_command *command)
{
	t_list		*node;

	command->type |= COMMAND_RUN;
	while (ft_stcksize(tree_node) > 0)
	{
		if (((t_action *)ft_stcktop(tree_node))->type == A_ARGS)
			break;
		node = ft_stckpopnode(tree_node);
		ft_lstadd(&command->actions, node);
	}
}

t_list	*generate_cmd_list(t_stack *tree_node)
{
	t_command	command;
	t_action	*action;
	t_list		*node;

	ft_bzero(&command, sizeof(t_command));
	node = ft_stckpopnode(tree_node);
	action = node->data;
	if (action->type == A_ASSIGN)
	{
		command_assign(tree_node, &command);
		ft_lstadd(&command.av, node);
	}
	else
	{
		command.av = action->data;
		command_assign(tree_node, &command);
		ft_lstdelone(&node, NULL);
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
	if (ft_stcksize(tree_node) == 0)
		return (FAILURE);
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
	t_list				*command_group;

	command_group = NULL;
	if (analyzer == NULL)
		analyzer = init_analyzer();
	get_token(resolve);
	while (resolve->state != P_END)
	{
		if (g_shell->analyzer_signal == TRUE)
		{
			signal_analyzer(resolve);
			break ;
		}
		if (resolve->state == P_STOP)
			generate_cmd_group(&command_group, &resolve->tree_node);
		(*analyzer)[resolve->state][resolve->token.type](resolve);
	}
	if (resolve->valid == 1)
		if (generate_cmd_group(&command_group, &resolve->tree_node) == FAILURE)
			return (NULL);
	analyzer_print_debug(g_shell, command_group);
	return	(command_group);
}
