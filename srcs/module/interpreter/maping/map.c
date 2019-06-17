/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 13:49:55 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/17 19:22:00 by skuppers         ###   ########.fr       */
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

void		*cmd_to_process(void *context, void *data)
{
	t_registry 	*shell;

	t_list		*node;
	t_list		*actions_redirects;
	t_process	process;
	t_command	*command;

	shell = context;
	command = data;
	ft_bzero(&process, sizeof(t_process));

//	ft_printf("\x1b[33m|| PRINTING ACTIONS ||\n\x1b[0m");
//	ft_lstiter(&command->actions, print_actions);
//	ft_printf("\x1b[33m|| ENDED PRINT ||\n\x1b[0m");

	actions_redirects = ft_lstsplit_if(&command->actions, NULL, redirect_or_other);
	process.redirects = ft_lstmap(actions_redirects, context, action_to_redirect, del_action);
	ft_lstiter_ctx(process.redirects, &process, check_redirect_error);
	process.av = ft_lsttotab(command->av, token_to_str);

/*-----------------------------------------------------------------
	char **pseudo_av = malloc(sizeof(char*) * 42);

	pseudo_av[0] = ft_strdup("$HOME");
	pseudo_av[1] = ft_strdup("sisi/$HOME");
	pseudo_av[2] = ft_strdup("$PWD/42sh.log");
	pseudo_av[3] = ft_strdup("toto/$NOTFOUND/tata");
	pseudo_av[4] = ft_strdup("\"$novariable\"");
	pseudo_av[5] = ft_strdup("\"$HOME\"");
	pseudo_av[6] = ft_strdup("\"seb/$HOME/op\"");
	pseudo_av[7] = ft_strdup("\'$LITTERAL\'");
	pseudo_av[8] = ft_strdup("\'$HOME\'");
	pseudo_av[9] = ft_strdup("\'$HOMO\'");
	pseudo_av[10] = ft_strdup("~");
	pseudo_av[11] = ft_strdup("~/");
	pseudo_av[12] = ft_strdup("~+");
	pseudo_av[13] = ft_strdup("~-");
	pseudo_av[14] = ft_strdup("~toto");
	pseudo_av[15] = ft_strdup("~skuppers");
	pseudo_av[16] = ft_strdup("\'literal string\'");
	pseudo_av[17] = ft_strdup("\"literal string\"");
	pseudo_av[18] = ft_strdup("\"plop\'litt\'plap\"");
	pseudo_av[19] = ft_strdup("\'plop\"litt\"plap\'");
	pseudo_av[20] = ft_strdup("~/$HOME");
	pseudo_av[21] = ft_strdup("$HOME/$PWD");
	pseudo_av[22] = ft_strdup("\'~/$HOME/$PWD\'");
	pseudo_av[23] = ft_strdup("\"~/$HOME/$PWD\"");
	pseudo_av[24] = ft_strdup("/~/");
	pseudo_av[25] = NULL;

	for (int x = 0; pseudo_av[x] != NULL; x++)
		expansion_pipeline(shell->intern, &(pseudo_av[x]));

-----------------------------------------------------------------------*/


	process.env = ft_lstmap(command->actions, NULL, token_to_var, free_node);

//	ft_printf("\x1b[33m|| PRINTING ASSIGNATIONS ||\n\x1b[0m");
//	ft_lstiter(process.env, print_var_lst);
//	ft_printf("\x1b[33m|| ENDED PRINT ||\n\x1b[0m");

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
