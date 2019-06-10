/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:42:30 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/10 10:21:50 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

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

void	execute_process(t_registry *shell, t_process *process, char **env)
{
	char		*pathname;

	pathname = NULL;
	//lstiter(redirects, do_redirects);
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
	pid_t			pid;

	env = generate_env(shell, process->env);
	pid = 0;
	pid = fork();
	ft_putchar('\n');
	if (pid < 0) // IF ERREUR
	{
		ft_dprintf(2, SH_GENERAL_ERROR INTEPRETER_FORK_ERROR);
		return;
	}
	else if (pid == 0) // IF CHILD
		execute_process(shell, process, env);
	else						//IF PARENT
		ft_freetab(&env);
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

void	expand_process(void *data)
{
	t_process *process;

	process = data;

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
		//PIPE ALL
		;
	ft_lstiter_ctx(job->processes, shell, run_process);
	job->pgid = head->pid;
	//CLOSE REDIRECTIONS;
	//CHECK WAIT CONDITION HERE;
	return ;
}

int8_t interpreter(t_registry *shell, t_list **cmd_group)
{
	t_list *job_lst;

	job_lst = ft_lstmap(*cmd_group, group_to_job, del_group);
	ft_lstdel(cmd_group, del_group);
	ft_lstiter_ctx(job_lst, shell, run_job);
	return (SUCCESS);
}
