/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 10:34:50 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/21 04:36:40 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

static void	child_process(t_registry *shell, t_process *process, char **env)
{
	char		*pathname;

	pathname = NULL;
	signal (SIGINT,  SIG_DFL);
	signal (SIGQUIT, SIG_DFL);
	signal (SIGPIPE, SIG_DFL);
	signal (SIGCHLD, SIG_DFL);

	signal (SIGTSTP, SIG_DFL);
	signal (SIGCONT, SIG_DFL);
	signal (SIGTTIN, SIG_DFL);
	signal (SIGTTOU, SIG_IGN);

	process->pid = getpid();
	setpgid(getpid(), *process->pgid);

	if (g_current_job != NULL && g_current_job->pgid == 0)
		g_current_job->pgid = process->pid;

//	ft_dprintf(3, "|->  Child process pid is %d\n", process->pid);
//	ft_dprintf(3, "|--> Child process grp is %d\n", *process->pgid);

	if (tcgetpgrp(STDOUT_FILENO) != *process->pgid)
	{
		tcsetpgrp(STDOUT_FILENO, *process->pgid);
//		ft_dprintf(3, "Attaching pid %d to the controlling terminal\n",
//						*process->pgid);
	}

//ft_dprintf(3, "\n");
	if (process->process_type & IS_BLT)
	{
		run_builtin(shell, process);
		exit(process->status);
	}
	if (process->process_type & IS_BIN)
		pathname = ft_hmap_getdata(&shell->hash.bin, process->av[0]);
	else
		pathname = process->av[0];
	ft_lstiter(process->redirects, do_redirect);
	execve(pathname, process->av, env);
	ft_dprintf(2, SH_GENERAL_ERROR INTEPRETER_EXECVE_ERROR);
	exit(FAILURE);
}

static void	parent_process(t_registry *shell, t_process *process, char ***env)
{
	if (process->process_type & IS_BIN)
		ft_hmap_hits(&shell->hash.bin, process->av[0]);
	ft_lstiter(process->redirects, close_redirect);

//	ft_dprintf(3, "|---> Parent process pid is %d\n", getpid());

	if (g_current_job != NULL && g_current_job->pgid == 0)
		g_current_job->pgid = process->pid;

	if (*process->pgid == 0)
		*process->pgid = process->pid;

	setpgid(process->pid, *process->pgid);

	ft_freetab(env);
}

void		fork_process(t_registry *shell, t_process *process)
{
	char			**env;

	env = generate_env(shell, process->env);
	if ((process->pid = fork()) < 0) // IF ERREUR
	{
		ft_dprintf(2, SH_GENERAL_ERROR INTEPRETER_FORK_ERROR);
		return;
	}
	else if (process->pid == 0)
		child_process(shell, process, env);
	else
		parent_process(shell, process, &env);
}

static void	update_intern(t_variable *variable, char *data)
{
	ft_strdel(&variable->data);
	variable->data = ft_strdup(data);
	if (variable->flag == EXPORT_VAR)
		variable->flag |= SET_VAR;
}

int			assign_intern(t_registry *shell, t_list **assign)
{
	t_list		*node;
	t_variable	*to_find;

	if (*assign == NULL)
		return (1);
	assign_intern(shell, &(*assign)->next);
	to_find = (*assign)->data;
	if ((node = ft_lstfind(shell->intern, to_find->name, find_var)))
	{
		update_intern(node->data, to_find->data);
		ft_lstdelone(assign, free_node);
	}
	else
	{
		(*assign)->next = NULL;
		ft_lstadd(&shell->intern, (*assign));
	}
	*assign = NULL;
	return (1);
}
