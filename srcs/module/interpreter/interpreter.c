/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:42:30 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/07 13:39:53 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

char	**generate_env()
{

}

void	run_builtin(t_registry *shell, t_process *process)
{
	int				ret;
	t_builtin		builtin;

	builtin = (t_builtin *)ft_hmap_getdata(&shell->hash.blt, process->av[0]);
	//setup redirect
	ret = builtin(shell, process->av);
	//check ret
	//reset redirect
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

int8_t	run_process(void *context, void *data)
{
	t_registry	*shell;
	t_process	*process;

	shell = context;
	process = data;
	if (get_process_type(shell, process) == FAILURE)
	{
		ft_dprintf(2, SH_GENERAL_ERROR SH_MALLOC_ERROR);
		return (FAILURE);
	}
	if (process->process_type & IS_NOTFOUND)
		ft_dprintf(2, SH_GENERAL_ERROR "%s" INTEPRETER_NOT_FOUND, process->av[0]);
	else if (process->process_type & (IS_ALONE | IS_BLT))
	{
		//redirect
		run_builtin(shell, process);
	}
	else
	{
		char			**env;

		env = generate_env();
		process->pid = fork();
		if (process->pid < 0) // IF ERREUR
		{
			ft_dprintf(2, SH_GENERAL_ERROR INTEPRETER_FORK_ERROR);
			return (FAILURE);
		}
		else if (process->pid == 0) // IF CHILD
			execute_process(shell, process, env);
		else						//IF PARENT
			ft_freetab(&env);
	}
	return (SUCCESS);
}

int8_t run_job(t_registry *shell, t_job *job)
{
	t_process	*head;

	head = job->processes->data;
	//EXPAND ALL JOB
	//OPEN & PIPE ALL JOB

	if (job->processes->next == NULL)
		head->process_type |= IS_ALONE;
	ft_lstiter_ctx(job->processes, shell, run_process); // RUN PROCESS(registre, process)
	job->pgid = head->pid;
	return (SUCCESS);
}

int8_t interpreter(t_registry *shell, t_list **cmd_group)
{
	t_list *job_lst;

	(void)shell;
	job_lst = ft_lstmap(*cmd_group, group_to_job, del_group); //CALLBACK DEL
	ft_lstdel(cmd_group, del_group);
	//lstiter(job_lst, run_job);
	/*	RUN		JOB
		while (process)
		{
			//CALL	EXPAND AV
			//CALL	EXPAND REDIRECT
			//SET	processTYPE
			el_pipeator_300();
			fork()
			{
				truc de pipe;
				while (redirect)
					lstiter(dup2);
				execve(process(av));
			}
			el_closatator_3000()
		}
		waitANY(job.pgid);

	*/

	return (SUCCESS);
}



