/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 13:49:55 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/11 18:09:57 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

void		set_process_pgid(void *context, void *data)
{
	t_job		*job;
	t_process	*process;

	job = context;
	process = data;
	process->pgid = &job->pgid;
	return ;
}

int	stdout_truncate(t_registry *shell, t_redirect *redirect, t_action *action)
{
	t_token		*token;
	char		*path;

	(void)shell;
	path = NULL;
	token = action->data->data;
	ft_asprintf(&path, "./%s", token->data);
	redirect->type |= FD_DUP;
	redirect->to = open(path, O_RDWR | O_TRUNC, 0766);
	redirect->from = STDOUT_FILENO;
	return (0);
}

t_redirection	*redirecter_init(void)
{
	static t_redirection	redirecter;

	redirecter[A_STDOUT_TRUNCATE_FILE] = stdout_truncate;
	redirecter[A_STDOUT_APPEND_FILE] = NULL;
	redirecter[A_STDIN_READ_FILE] = NULL;
	return (&redirecter);
}

void		*action_to_redirect(void *context, void *data)
{
	static t_redirection	*redirecter;
	t_registry				*shell;
	t_list					*node;
	t_action				*action;
	t_redirect				redirect;

	if (redirecter == NULL)
		redirecter = redirecter_init();
	action = data;
	shell = context;
	ft_bzero(&redirect, sizeof(t_redirect));
	if ((*redirecter)[action->type](shell, &redirect, action))
		return (NULL);
	node = ft_lstnew(&redirect, sizeof(t_redirect));
	return (node);
}

void		*cmd_to_process(void *context, void *data)
{
	t_list		*node;
	t_list		*actions_redirects;
	t_process	process;
	t_command	*command;

	command = data;
	ft_bzero(&process, sizeof(t_process));
	actions_redirects = ft_lstsplit_if(&command->actions, NULL, redirect_or_other);
	process.redirects = ft_lstmap(actions_redirects, context, action_to_redirect, del_action);
	process.av = ft_lsttotab(command->av, token_to_str);
	process.env = ft_lstmap(command->actions, NULL, token_to_var, free_node);
	ft_lstdel(&actions_redirects, del_action);
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
	job.job_type = group->group_type;
	job.processes = ft_lstmap(group->command_list, context, cmd_to_process, del_command);
	node = ft_lstnew(&job, sizeof(t_job));
	ft_lstiter_ctx(job.processes, node->data, set_process_pgid);
	return (node);
}
