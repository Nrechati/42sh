/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:42:30 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/11 10:35:21 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>
#include <stdio.h>

void	run_builtin(t_registry *shell, t_process *process)
{
	int				ret;
	t_builtin		builtin;

	builtin = ft_hmap_getdata(&shell->hash.blt, process->av[0]);
	ret = builtin(shell, process->av);
	(void)ret;
	return ;
}

void	run_process(void *context, void *data)
{
	t_registry	*shell;
	t_process	*process;

	shell = context;
	process = data;
	if (get_process_type(shell, process) == FAILURE)
	{
		ft_dprintf(2, SH_GENERAL_ERROR SH_MALLOC_ERROR);
		return;
	}
	if (process->process_type & IS_NOTFOUND)
		ft_dprintf(2, SH_GENERAL_ERROR "%s" INTEPRETER_NOT_FOUND, process->av[0]);
	else if (process->process_type == (IS_ALONE | IS_BLT))
	{
		//redirect setup
		run_builtin(shell, process);
		//redirect init;
	}
	else
		fork_process(shell, process);
	return;
}

void	run_job(void *context, void *data)
{
	t_registry	*shell;
	t_job		*job;
	t_process	*head;

	shell = context;
	job = data;
	head = job->processes->data;
	//EXPAND ALL JOB
	//OPEN ALL JOB
	if (job->processes->next == NULL)
		head->process_type |= IS_ALONE;
	else
		setup_pipe(job->processes);
	ft_lstiter_ctx(job->processes, shell, run_process);

	ft_lstiter(job->processes, print_process);
	//CLOSE REDIRECTIONS;
	//CHECK WAIT CONDITION HERE;
	waiter(job);
	return ;
}

int8_t interpreter(t_registry *shell, t_list **cmd_group)
{
	t_list *job_lst;

	signal (SIGINT, SIG_DFL);
	signal (SIGQUIT, SIG_DFL);
	signal (SIGTSTP, SIG_DFL);
	signal (SIGTTIN, SIG_DFL);
	signal (SIGTTOU, SIG_DFL);
	signal (SIGCHLD, SIG_DFL);
	signal (SIGPIPE, SIG_DFL);
	job_lst = ft_lstmap(*cmd_group, group_to_job, del_group);
	ft_lstdel(cmd_group, del_group);
	ft_lstiter_ctx(job_lst, shell, run_job);
	return (SUCCESS);
}
