/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 10:34:50 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/07 14:21:29 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

static uint8_t	check_cmd_path(char *data)
{
	struct stat	stat;

	if (lstat(data, &stat))
	{
		ft_dprintf(2, "42sh: %s: no such file or directory\n", data);
		return (FALSE);
	}
	if (stat.st_mode & S_IFDIR)
		ft_dprintf(2, "42sh: %s: Is a directory\n", data);
	else if (access(data, X_OK))
		ft_dprintf(2, "42sh: %s: Permission denied\n", data);
	else
		return (TRUE);
	return (FALSE);
}

static void		run_child(t_process *process, char **env)
{
	char		*pathname;

	pathname = NULL;
	if (ft_lstiter_ctx(process->redirects, NULL, do_redirect) == FAILURE)
		exit(1);
	ft_lstiter(process->redirects, close_redirect);
	if (process->type & IS_BIN)
		pathname = ft_hmap_getdata(&g_shell->hash.bin, process->av[0]);
	else if (process->type & IS_ABS)
	{
		if (check_cmd_path(process->av[0]) == TRUE)
			pathname = process->av[0];
	}
	else if (process->type & IS_NOTFOUND)
		ft_dprintf(2, "42sh: %s: command not found\n", process->av[0]);
	if (pathname != NULL)
	{
		if (execve(pathname, process->av, env) == FAILURE)
			ft_dprintf(2, "42sh: execution error\n");
	}
	exit(1);
}

static void		child_process(t_process *process, char **env, uint8_t fg)
{
	init_exec_signals();
	process->pid = getpid();
	if (*process->pgid == 0)
		*process->pgid = process->pid;
	setpgid(process->pid, *process->pgid);
	if (fg == TRUE)
	{
//		if (tcgetpgrp(STDOUT_FILENO) != *process->pgid)
			tcsetpgrp(STDOUT_FILENO, *process->pgid);
	}
	if (process->type & IS_BLT)
	{
		run_builtin(process, fg);
		exit(process->status);
	}
	else
		run_child(process, env);
}

static void		parent_process(t_process *process, char ***env, uint8_t fg)
{
	if (process->type & IS_BIN)
		ft_hmap_hits(&g_shell->hash.bin, process->av[0]);
	if (*process->pgid == 0)
		*process->pgid = process->pid;
	setpgid(process->pid, *process->pgid);
	if (fg == FALSE)
	{
		tcsetpgrp(STDOUT_FILENO, g_shell->pid);
		term_mode(TERMMODE_EXEC);
	}
	else
		tcsetpgrp(STDOUT_FILENO, *process->pgid);
	ft_freetab(env);
}

void			fork_process(t_process *process, uint8_t foreground, int pipe)
{
	char			**env;

	if ((env = generate_env(g_shell, process->env)) == NULL)
	{
		process->type |= IS_EXP_ERROR;
		return ;
	}
	if ((process->pid = fork()) < 0)
	{
		ft_freetab(&env);
		ft_dprintf(2, "42sh: fork error\n");
		return ;
	}
	else if (process->pid == 0)
		child_process(process, env, foreground);
	else
		parent_process(process, &env, foreground);
	if (pipe)
		close(pipe);
}
