/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 10:34:50 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/02 12:43:25 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

uint8_t	check_cmd_path(char *data)
{
	struct stat	stat;

	if (lstat(data, &stat))
	{
		ft_dprintf(2, "42sh: no such file or directory: %s\n", data);
		return (FALSE);
	}
	if (stat.st_mode & S_IFDIR)
		ft_dprintf(2, "42sh: %s: Is a directory\n", data);
	else if (!(stat.st_mode & S_IRUSR))
		ft_dprintf(2, "42sh: %s: Permission denied\n", data);
	else
		return (TRUE);
	return (FALSE);
}

static void	child_process(__unused t_registry *shell, t_process *process, __unused char **env)
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
	if (tcgetpgrp(STDOUT_FILENO) != *process->pgid)
		tcsetpgrp(STDOUT_FILENO, *process->pgid);
	if (process->process_type & IS_BLT)
	{
		run_builtin(shell, process);
		exit(process->status);
	}
	if (process->process_type & IS_BIN)
		pathname = ft_hmap_getdata(&shell->hash.bin, process->av[0]);
	else if (process->process_type & IS_ABS)
	{
		if (check_cmd_path(process->av[0]) == TRUE)
			pathname = process->av[0];
	}
	else if (process->process_type & IS_NOTFOUND)
		ft_dprintf(2, SH_GENERAL_ERROR "%s" INTERPRETER_NOT_FOUND, process->av[0]);
	ft_lstiter(process->redirects, do_redirect);
	ft_lstiter(process->redirects, close_redirect);
	if (pathname != NULL)
	{
		#ifndef NOEXEC
		execve(pathname, process->av, env);
		#else
		(void)env;
		#endif
	}
	exit(FAILURE);
}

static void	parent_process(t_registry *shell, t_process *process, char ***env)
{
	if (process->process_type & IS_BIN)
		ft_hmap_hits(&shell->hash.bin, process->av[0]);
	//ft_lstiter(process->redirects, close_redirect);
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
	if ((process->pid = fork()) < 0)
	{
		ft_dprintf(2, SH_GENERAL_ERROR INTERPRETER_FORK_ERROR);
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
	if (assign_intern(shell, &(*assign)->next) == TRUE)
	{
		to_find = (*assign)->data;
		if (ft_strequ(to_find->name, "PATH"))
			ft_hmap_free_content(&(shell->hash.bin), free);
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
