/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 13:49:55 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/17 19:23:46 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		set_process_pgid(void *context, void *data)
{
	t_job		*job;
	t_process	*process;

	job = context;
	process = data;
	process->pgid = &job->pgid;
	return ;
}

t_redirection	*redirecter_init(void)
{
	static t_redirection	redirecter;

	redirecter[A_STDOUT_TRUNCATE_FILE] = stdout_truncate;
	redirecter[A_STDOUT_APPEND_FILE] = stdout_append;
	redirecter[A_STDIN_READ_FILE] = stdin_readfile;
	redirecter[A_IO_TRUNCATE_FILE] = io_truncate;
	redirecter[A_IO_APPEND_FILE] = io_append;
	redirecter[A_IO_READ_FILE] = io_readfile;
	redirecter[A_DUP] = duplicate_fd;
	redirecter[A_CLOSE] = close_fd;
	redirecter[A_MOVE] = move_fd;
	redirecter[A_HEREDOC] = heredoc;
	redirecter[A_HEREDOC_TRIM] = move_fd;
	redirecter[A_IO_HEREDOC] = move_fd;
	redirecter[A_IO_HEREDOC_TRIM] = move_fd;
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
	(*redirecter)[action->type](shell, &redirect, action);
	node = ft_lstnew(&redirect, sizeof(t_redirect));
	return (node);
}

void	*token_to_intern_var(__unused void *context, void *data)
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
	var.flag = SET_VAR;
	var.name = ft_strdup(name_token->data);
	var.data = ft_strdup(data_token->data);
	node = ft_lstnew(&var, sizeof(t_variable));
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
	if (command->type == COMMAND_ASSIGN)
	{
		process.av = NULL;
		process.env = ft_lstmap(command->av, context, token_to_intern_var, free_node);
		process.process_type = IS_ASSIGN;
	}
	else
	{
		actions_redirects = ft_lstsplit_if(&command->actions, NULL, redirect_or_other);
		process.redirects = ft_lstmap(actions_redirects, context, action_to_redirect, del_action);
		ft_lstiter_ctx(process.redirects, &process, check_redirect_error);
		process.av = ft_lsttotab(command->av, token_to_str);
		process.env = ft_lstmap(command->actions, context, token_to_var, free_node);
		ft_lstdel(&actions_redirects, del_action);
	}
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
