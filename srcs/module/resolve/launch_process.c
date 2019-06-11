/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:13:52 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/11 11:51:58 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

static char		**str_lst_to_tab(t_list *alst)
{
	uint32_t	i;
	size_t		size;
	t_variable	*variable;
	char		*env;
	char		**tabs;

	i = 0;
	size = list_export_size(alst);
	if ((tabs = (char **)ft_malloc(sizeof(char *) * (size + 1))) == NULL)
		return (NULL);
	while (alst != NULL)
	{
		variable = (t_variable *)alst->data;
		if (variable->flag & EXPORT_VAR)
		{
			env = NULL;
			ft_asprintf(&env, "%s=%s", variable->name, variable->data);
			tabs[i] = env;
			i++;
		}
		alst = alst->next;
	}
	tabs[i] = NULL;
	return (tabs);
}

static void		execute_process(t_process *process,
					t_registry *shell, char **env)
{
	char	*pathname;

	pathname = NULL;
	define_execution_signals();
	ft_lstiter(process->fd, redirect);
	if (ft_hmap_getdata(&shell->hash.blt, process->av[0]) != NULL)
		exit(((t_builtin)ft_hmap_getdata(&shell->hash.blt
						, process->av[0]))(shell, process->av));
	else if (ft_hmap_getdata(&shell->hash.bin, process->av[0]) != NULL)
		execve(ft_hmap_getdata(&shell->hash.bin, process->av[0])
				, process->av, env);
	else if (process->av[0][0] == '.' || process->av[0][0] == '/')
		execve(process->av[0], process->av, env);
	ft_dprintf(2, "42sh: command not found: %s\n", process->av[0]);
	exit(FAILURE);
}

static int8_t	launch_builtin(t_registry *shell, t_process *process)
{
	t_builtin		f;

	if (!(f = ft_hmap_getdata(&shell->hash.blt, process->av[0])))
		return (FAILURE);
	shell->cur_fd.in = 0;
	shell->cur_fd.out = 1;
	shell->cur_fd.err = 2;
	ft_lstiter(process->fd, get_blt_fd);
	f(shell, process->av);
	shell->cur_fd.in = 0;
	shell->cur_fd.out = 1;
	shell->cur_fd.err = 2;
	return (SUCCESS);
}

static int8_t	is_exec(t_registry *shell, t_process *process)
{
	void	*hash;
	char	*pathname;

	hash = NULL;
	pathname = NULL;
	if (ft_hmap_getdata(&shell->hash.blt, process->av[0]) == NULL
			&& (hash = ft_hmap_getdata(&shell->hash.bin, process->av[0])) == NULL
			&& find_in_path(shell, process->av[0], &pathname) != SUCCESS
			&& !(process->av[0][0] == '.' || process->av[0][0] == '/'))
	{
		ft_dprintf(2, "42sh: command not found: %s\n", process->av[0]);
		return (FALSE);
	}
	if (hash != NULL)
		if (ft_hmap_hits(&shell->hash.bin, process->av[0]) != SUCCESS)
			ft_dprintf(2, "42sh: error hitting bin\n");
	if (pathname != NULL)
	{
		hash_one(shell, process->av[0], pathname);
		if (ft_hmap_hits(&shell->hash.bin, process->av[0]) != SUCCESS)
			ft_dprintf(2, "42sh: error hitting bin\n");
	}
	return (TRUE);
}

int8_t			launch_process(t_job *job, t_process *process,
						t_registry *shell)
{
	pid_t		pid;
	char		**env;

	if (is_exec(shell, process) == FALSE)
		return (SUCCESS);
	if (process->av == NULL)
		return (SUCCESS);
	if (job->process_list->next == NULL
			&& launch_builtin(shell, process) == SUCCESS)
		return (SUCCESS);
	env = str_lst_to_tab(shell->intern);
	if ((pid = fork()) == SUCCESS)
		execute_process(process, shell, env);
	else if (pid < 0)
	{
		ft_dprintf(2, "[ERROR]: Fork() failed.\n");
		ft_freetab(&env);
		return (FAILURE);
	}
	ft_freetab(&env);
	process->pid = pid;
	job->pgid = job->pgid ? job->pgid : pid;
	return (SUCCESS);
}
