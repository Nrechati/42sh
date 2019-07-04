/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 13:49:55 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/04 14:47:04 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		*set_redirect(void *context, void *data)
{
	static t_redirection	*redirecter;
	t_list					*node;
	t_action				*action;
	t_redirect				redirect;

	(void)context;
	if (redirecter == NULL)
		redirecter = redirecter_init();
	action = data;
	ft_bzero(&redirect, sizeof(t_redirect));
	(*redirecter)[action->type](&redirect, action);
	node = ft_lstnew(&redirect, sizeof(t_redirect));
	return (node);
}

void		*set_intern(void *context, void *data)
{
	t_list		*node;
	t_list		*ptr;
	t_token		*name_token;
	t_token		*data_token;
	t_variable	var;

	(void)context;
	ptr = ((t_action *)data)->data;
	name_token = ptr->data;
	data_token = ptr->next->data;
	ft_bzero(&var, sizeof(t_variable));
	var.flag = SET_VAR;
	var.name = ft_strdup(name_token->data);
	var.data = ft_strdup(data_token->data);
	node = ft_lstnew(&var, sizeof(t_variable));
	return (node);
}

void		set_process(t_process *proc, t_command *command, void *context)
{
	t_list		*redirect;

	redirect = ft_lstsplit_if(&command->actions, NULL, redirect_or_other);
	proc->redirects = ft_lstmap(redirect, context, set_redirect, del_action);
	if (ft_lstiter_ctx(proc->redirects, proc, check_redirect_error) == FAILURE)
	{
		ft_lstdel(&redirect, del_action);
		ft_lstdel(&proc->redirects, close_redirect);
		return ;
	}
	proc->av = ft_lsttotab(command->av, token_to_str);
	proc->env = ft_lstmap(command->actions, context, token_to_var, free_node);
	ft_lstdel(&redirect, del_action);
	return ;
}

void		*cmd_to_process(void *context, void *data)
{
	t_list		*node;
	t_process	process;
	t_command	*command;

	command = data;
	ft_bzero(&process, sizeof(t_process));
	if (command->type == COMMAND_ASSIGN)
	{
		process.av = NULL;
		process.env = ft_lstmap(command->av, context, set_intern, free_node);
		process.type = IS_ASSIGN;
		ft_lstdel(&command->av, del_action);
	}
	else
		set_process(&process, command, context);
	node = ft_lstnew(&process, sizeof(t_process));
	return (node);
}

void		*group_to_job(void *context, void *data)
{
	t_job		job;
	t_list		*node;
	t_group		*group;

	group = data;
	ft_bzero(&job, sizeof(t_job));
	job.state = PENDING;
	job.type = group->type;
	job.processes = ft_lstmap(group->command_list, context
							, cmd_to_process, del_command);
	node = ft_lstnew(&job, sizeof(t_job));
	ft_lstiter_ctx(job.processes, node->data, set_process_pgid);
	return (node);
}
