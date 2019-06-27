/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 10:34:50 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/27 18:57:31 by cempassi         ###   ########.fr       */
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
	if (*process->pgid == 0)
		*process->pgid = process->pid;

	setpgid(process->pid, *process->pgid);
//	ft_dprintf(3, "|->  Child process pid is %d\n", process->pid);
//	ft_dprintf(3, "|--> Child process grp is %d\n", *process->pgid);
	if (tcgetpgrp(STDOUT_FILENO) != *process->pgid)
	{
		tcsetpgrp(STDOUT_FILENO, *process->pgid);
//		ft_dprintf(3, "Attaching pid %d to the controlling terminal\n",
//						*process->pgid);
	}

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
#ifndef NOEXEC
	execve(pathname, process->av, env);
	ft_dprintf(2, SH_GENERAL_ERROR INTEPRETER_EXECVE_ERROR);
	exit(FAILURE);
#else
	(void)env;
	exit(SUCCESS);
#endif
}

static void	parent_process(t_registry *shell, t_process *process, char ***env)
{
	if (process->process_type & IS_BIN)
		ft_hmap_hits(&shell->hash.bin, process->av[0]);
	ft_lstiter(process->redirects, close_redirect);

	ft_dprintf(3, "|---> Parent process pid is %d\n", getpid());

	if (*process->pgid == 0)
		*process->pgid = process->pid;

	setpgid(process->pid, *process->pgid);

	ft_freetab(env);
}

void		fork_process(t_registry *shell, t_process *process)
{
	char			**env;

	if ((env = generate_env(shell, process->env)) == NULL)
	{
		process->process_type |= IS_EXP_ERROR;
		return ;
	}
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

static int	update_intern(t_variable *variable, char *data)
{
	if (variable->flag & READONLY_VAR)
	{
		ft_dprintf(STDERR_FILENO,"42sh:`%s': not a valid identifier\n"
				, variable->name);
		return (FAILURE);
	}
	ft_strdel(&variable->data);
	variable->data = expansion_pipeline(g_shell->intern, data);
	if (variable->flag == EXPORT_VAR)
		variable->flag |= SET_VAR;
	return (SUCCESS);
}

int			insert_intern(t_list **intern, t_list *node)
{
	t_variable 	*variable;
	char		*holder;

	variable = node->data;
	if ((holder = expansion_pipeline(*intern, variable->data)) == NULL)
		return (FAILURE);
	ft_strdel(&variable->data);
	variable->data = holder;
	node->next = NULL;
	ft_lstadd(intern, node);
	return (SUCCESS);
}

int			assign_intern(t_registry *shell, t_list **assign)
{
	t_list		*node;
	t_variable	*to_find;

	if (*assign == NULL)
		return (TRUE);
	if (assign_intern(shell, &(*assign)->next) == 1)
	{
		to_find = (*assign)->data;
		if ((node = ft_lstfind(shell->intern, to_find->name, find_var)))
		{
			if (update_intern(node->data, to_find->data) == FAILURE)
				return (FAILURE);
			ft_lstdelone(assign, free_node);
		}
		else
		{
			if (insert_intern(&shell->intern, *assign) == FAILURE)
				return (FAILURE);
		}
		*assign = NULL;
		return (TRUE);
	}
	return (FAILURE);
}
