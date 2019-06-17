/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 10:34:50 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/17 15:50:49 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

void	assign_intern(t_registry *shell, t_list *assign)
{
	t_list		*node;
	t_variable	*variable;
	t_variable	*to_find;

	if (assign != NULL)
	{
		assign_intern(shell, assign->next);
		to_find = assign->data;
		if ((node = ft_lstfind(shell->intern, to_find->name, find_var)))
		{
			variable = node->data;
			ft_strdel(&variable->data);
			variable->data = ft_strdup(to_find->data);
		}
		else
		{
			assign->next = NULL;
			ft_lstadd(&shell->intern, assign);
		}
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
		//setpgid(getpid(), *process->pgid);
		execute_process(shell, process, env);
	}
	else
	{						//IF PARENT
		if (process->process_type & IS_BIN)
			ft_hmap_hits(&shell->hash.bin, process->av[0]);
		ft_lstiter(process->redirects, close_redirect);
		if (*process->pgid == 0)
			*process->pgid = process->pid;
		//setpgid(process->pid, *process->pgid);
		ft_freetab(&env);
	}
}
