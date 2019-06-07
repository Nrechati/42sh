/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 13:49:55 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/07 09:59:56 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		*token_to_var(void *data)
{
	t_list		*node;
	t_list		*ptr;
	t_token		*name_token;
	t_token		*data_token;
	t_variable	var;

	ptr = ((t_action *)data)->data;
	name_token = ptr->data;
	data_token = ptr->next->data;
	ft_bzero(&var, sizeof(t_variable));
	var.flag = EXPORT_VAR;
	var.name = ft_strdup(name_token->data);
	var.data = ft_strdup(data_token->data);
	node = ft_lstnew(&var, sizeof(t_variable));
	return (node);
}

char		*token_to_str(void *data)
{
	char		*str;
	t_token		*token;

	token = data;
	str = ft_strdup(token->data);
	if (str == NULL)
		return (NULL);
	return (str);
}

void		*actions_to_redirects(void *data)
{
	return (NULL);
}

int			*redirect_or_other(void *action, __unused void *data)
{
	enum e_actions		type;

	type = ((t_action *)action)->action;
	if (type == A_ASSIGN)
		return (FALSE);
	return (TRUE);
}

void		*cmd_to_process(void *data)
{
	t_list		*node;
	t_list		*actions_redirects;
	t_process	process;
	t_command	*command;

	command = data;
	ft_bzero(&process, sizeof(t_process));
	actions_redirects = ft_lstsplit_if(command->actions, NULL, redirect_or_other);
//	process.redirects = ft_lstmap(actions_redirects, action_to_redirects, del_cb);
	process.av = ft_lsttotab(command->av, token_to_str);
	process.env = ft_lstmap(command->actions, token_to_var, NULL); //CALLBACK DEL

	//LSTDEL action_redirect

	node = ft_lstnew(&process, sizeof(t_process));
	return (node);
}

void		*group_to_job(void *data)
{
	t_job		job;
	t_list		*node;
	t_group		*group;

	group = data;
	ft_bzero(&job, sizeof(t_job));
	job.job_type = group->group_type;
	job.processes = ft_lstmap(group->command_list, cmd_to_process, NULL); //CALLBACK DEL
	node = ft_lstnew(&job, sizeof(t_job));
	return (node);
}
