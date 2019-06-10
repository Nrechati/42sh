/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:42:30 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/10 19:48:23 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>
#include <stdio.h>

int		is_export(void *data, __unused void *to_find)
{
	t_variable *variable;

	variable = data;
	return (variable->flag & (EXPORT_VAR | SET_VAR));
}

int		copy_var(void *src, void *dest)
{
	t_variable *source;
	t_variable *destination;

	source = src;
	destination = dest;
	destination->name = ft_strdup(source->name);
	destination->data = ft_strdup(source->data);
	return (0);
}

void	variable_update(void *context, void *data)
{
	t_list 		*tmp_env;
	t_variable	*variable;

	tmp_env = context;
	variable = data;
	add_var(&tmp_env, variable->name, variable->data, variable->flag);
}

char	*variable_to_tab(void *data)
{
	t_variable	*variable;
	char		*str;

	variable = data;
	str = NULL;
	ft_asprintf(&str, "%s=%s", variable->name, variable->data);
	return (str);
}

char	**generate_env(t_registry *shell, t_list *local_env)
{
	char	**env;
	t_list	*tmp_env;

	tmp_env = ft_lstfilter(shell->intern, NULL, is_export, copy_var);
	ft_lstiter_ctx(local_env, tmp_env, variable_update);
	env = ft_lsttotab(tmp_env, variable_to_tab);
	return (env);
}

void	run_builtin(t_registry *shell, t_process *process)
{
	int				ret;
	t_builtin		builtin;

	builtin = ft_hmap_getdata(&shell->hash.blt, process->av[0]);
	ret = builtin(shell, process->av);
	//check ret
	(void)ret;
	return ;
}

void	close_redirects(void *data)
{
	t_redirect	*redirect;

	redirect = data;
	if (redirect->type & FD_PIPE)
		close(redirect->to);
}

void	iter_redirect(t_list *processes)
{
	t_process	*current;

	while (processes != NULL)
	{
		current = processes->data;
		ft_lstiter(current->redirects, close_redirects);
		processes = processes->next;
	}
}

void	do_redirect(void *data)
{
	t_redirect	*redirect;

	redirect = data;
	if (redirect->type & FD_PIPE)
	{
		ft_dprintf(2, "[FORK] redirect to %d from %d\n", redirect->to, redirect->from);
		dup2(redirect->to, redirect->from);
	}
	else if (redirect->type & FD_CLOSE)
	{
		ft_dprintf(2, "[FORK]closing %d\n", redirect->to);
		close(redirect->to);
	}
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

t_list	*close_pipe(int to_close)
{
	t_list		*node;
	t_redirect	pipe;

	ft_bzero(&pipe, sizeof(t_redirect));
	pipe.to = to_close;
	pipe.type |= FD_CLOSE;
	node = ft_lstnew(&pipe, sizeof(t_redirect));
	return (node);
}

t_list	*create_pipe(int to, int from)
{
	t_list		*node;
	t_redirect	pipe;

	ft_bzero(&pipe, sizeof(t_redirect));
	pipe.to = to;
	pipe.from = from;
	pipe.type |= FD_PIPE;
	node = ft_lstnew(&pipe, sizeof(t_redirect));
	return (node);
}

int8_t	setup_pipe(t_list *processess)
{
	int			pipe_fd[2];
	t_list		*pipe_node;
	t_list		*close_node;
	t_process	*current;
	t_process	*next;

	if (processess->next == NULL)
		return (SUCCESS);
	current = processess->data;
	next = processess->next->data;
	if (pipe(pipe_fd) == FAILURE)
		return (FAILURE);
	if ((pipe_node = create_pipe(pipe_fd[1], STDOUT_FILENO)) == NULL)
		return (FAILURE);
	if ((close_node = close_pipe(pipe_fd[0])) == NULL)
		return (FAILURE);
	ft_lstaddback(&current->redirects, pipe_node);
	ft_lstaddback(&current->redirects, close_node);
	if ((pipe_node = create_pipe(pipe_fd[0], STDIN_FILENO)) == NULL)
		return (FAILURE);
	if ((close_node = close_pipe(pipe_fd[1])) == NULL)
		return (FAILURE);
	ft_lstadd(&next->redirects, pipe_node);
	ft_lstadd(&next->redirects, close_node);
	return (setup_pipe(processess->next));
}

void	update_pid(t_list *processes)
{
	t_process	*current;

	while (processes)
	{
		current = processes->data;
		if (WIFEXITED(current->status))
				current->completed = 1;
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
	return (TRUE);
}

int8_t	waiter(t_job *job)
{
	int		status;
	pid_t	pid;

	size_t  nbr_of_process = ft_lstlen(job->processes);

	ft_printf("waiter pgid: %d\n", job->pgid);
	while (nbr_of_process > 0)
	{
		pid = wait(&status);
		ft_printf("PID %ld exited\n", (long)pid);
		--nbr_of_process;
	}

//	while (all_is_done(job->processes) == FALSE)
//	{
//		status = 0;
//		pid = waitpid(WAIT_ANY, &status, WEXITED | WNOHANG);
//		//update_pid(job->processes);
//	}
	return (SUCCESS);
}


void	print_process(void *data)
{
	t_process *process;

	process = data;
	ft_showtab(process->av);
	ft_printf("process->type: %d | process->pid: %d | process->pgid: %d\n"
			, process->process_type
			, process->pid
			, *process->pgid);
}

void	print_job(void *data)
{
	t_job *job;

	job = data;
	ft_printf("pgid : %s | job_type: %u\n"
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
	iter_redirect(job->processes);
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
	job_lst = ft_lstmap(*cmd_group, group_to_job, del_group);
	ft_lstdel(cmd_group, del_group);
	ft_lstiter_ctx(job_lst, shell, run_job);
	return (SUCCESS);
}
