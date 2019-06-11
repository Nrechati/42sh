/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:42:30 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/11 09:53:01 by nrechati         ###   ########.fr       */
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

void	close_redirects(void *data)
{
	t_redirect	*redirect;

	redirect = data;
	if (redirect->type & FD_PIPE_OUT || redirect->type & FD_PIPE_IN)
		close(redirect->to);
}

void	do_redirect(void *data)
{
	t_redirect	*redirect;

	redirect = data;
	if (redirect->type & FD_PIPE_OUT)
	{
		dup2(redirect->to, STDOUT_FILENO);
		close(redirect->from);
	}
	else if (redirect->type & FD_PIPE_IN)
	{
		dup2(redirect->to, STDIN_FILENO);
		close(redirect->from);
	}
	else if (redirect->type & FD_CLOSE)
		close(redirect->to);
}

void	execute_process(t_registry *shell, t_process *process, char **env)
{
	char		*pathname;

	pathname = NULL;
	signal (SIGINT, SIG_DFL);
	signal (SIGQUIT, SIG_DFL);
	signal (SIGTSTP, SIG_DFL);
	signal (SIGTTIN, SIG_DFL);
	signal (SIGTTOU, SIG_DFL);
	signal (SIGCHLD, SIG_DFL);
	signal (SIGPIPE, SIG_DFL);
	ft_lstiter(process->redirects, do_redirect);
	if (process->process_type & IS_BLT)
	{
		run_builtin(shell, process);
		exit(process->status);
	}
	if (process->process_type & IS_BIN)
		pathname = ft_hmap_getdata(&shell->hash.bin, process->av[0]);
	else
		pathname = process->av[0];
	execve(pathname, process->av, env);
	ft_dprintf(2, SH_GENERAL_ERROR INTEPRETER_EXECVE_ERROR);
	exit(FAILURE);
}

void	fork_process(t_registry *shell, t_process *process)
{
	char			**env;

	env = generate_env(shell, process->env);
	process->pid = fork();
	if (process->pid < 0) // IF ERREUR
	{
		ft_dprintf(2, SH_GENERAL_ERROR INTEPRETER_FORK_ERROR);
		return;
	}
	else if (process->pid == 0) // IF CHILD
	{
		setpgid(getpid(), *process->pgid);
		execute_process(shell, process, env);
	}
	else
	{						//IF PARENT
		ft_printf("fork process pid : %d\n", process->pid);
		ft_lstiter(process->redirects, close_redirects);
		if (*process->pgid == 0)
			*process->pgid = process->pid;
		setpgid(process->pid, *process->pgid);
		ft_freetab(&env);
	}
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

void	update_pid(t_list *processes, pid_t pid)
{
	t_process	*current;

	while (processes)
	{
		current = processes->data;
		if (current->pid == pid)
		{
			current->completed = 1;
			ft_dprintf(2, "\x1b[32m%s completed with success with PID %d\n\x1b[0m"
					, current->av[0]
					, pid);
			return ;
		}
		processes = processes->next;
	}
	return ;
}

uint8_t	all_is_done(t_list *processes)
{
	t_process	*current;

	while (processes)
	{
		current = processes->data;
		if (current->completed == FALSE)
			return (FALSE);
		processes = processes->next;
	}
	ft_dprintf(2, "\x1b[32mAll is Done\n\x1b[0m");
	return (TRUE);
}

int8_t	waiter(t_job *job)
{
	int		status;
	pid_t	pid;

	ft_printf("\x1b[33mWaiter pgid: %d\n\x1b[0m", job->pgid);
	while (all_is_done(job->processes) == FALSE)
	{
		status = 0;
		pid = waitpid(WAIT_ANY, &status, WNOHANG);
		if (pid)
			update_pid(job->processes, pid);
	}
	return (SUCCESS);
}

void	print_process(void *data)
{
	t_process *process;

	process = data;
	ft_showtab(process->av);
	ft_printf("\x1b[33mprocess->type: %d | process->pid: %d | process->pgid: %d\n\x1b[0m"
			, process->process_type, process->pid, *process->pgid);
}

void	print_job(void *data)
{
	t_job *job;

	job = data;
	ft_printf("\x1b[33mpgid : %s | job_type: %u\n\x1b[0m"
			, job->pgid
			, job->job_type);
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
