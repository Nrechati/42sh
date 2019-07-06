/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 13:46:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/07 01:37:23 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

static void	setup_builtin(t_process *process, uint8_t *std)
{
	if (process->type & IS_ALONE)
		ft_lstiter_ctx(process->redirects, std, builtin_redirect);
	else
		ft_lstiter_ctx(process->redirects, NULL, do_redirect);
}

void		run_builtin(t_process *process)
{
	char			*tty_name;
	uint8_t			std;
	t_builtin		builtin;
	int				fd;

	std = 0;
	tty_name = ttyname(STDIN_FILENO);
	setup_builtin(process, &std);
	close(STDIN_FILENO);
	if (ft_strequ(process->av[0], "env"))
	{
		fd = open(tty_name, O_RDWR);
		if (fd != 0)
			close(fd);
	}
	builtin = ft_hmap_getdata(&g_shell->hash.blt, process->av[0]);
	process->status = builtin(g_shell, process->av, process);
	if (process->type & IS_ALONE)
	{
		default_io(std, tty_name);
		process->completed = 1;
	}
	ft_lstiter(process->redirects, close_redirect);
	return ;
}

static void	run_type_selection(t_process *process, int pipe)
{
	if (process->type & IS_ASSIGN)
		process->completed = assign_intern(g_shell, &process->env);
	else if (process->av == NULL || process->av[0] == NULL)
		process->completed = 1;
	else if (process->type == (IS_ALONE | IS_BLT))
		run_builtin(process);
	else
		fork_process(process, pipe);
}

int			run_process(t_process *process, int pipe)
{
	setup_redirect(process);
	if (process->type & (IS_DUP_FAILED | IS_CRITICAL | IS_OPEN_FAILED))
	{
		add_var(&g_shell->intern, "?", "1", READONLY_VAR);
		return (process->completed = FAILURE);
	}
	if (expand_process(g_shell->intern, process) == FAILURE)
	{
		add_var(&g_shell->intern, "?", "1", READONLY_VAR);
		process->completed = 1;
		return (FAILURE);
	}
	if (get_process_type(g_shell, process) == FAILURE)
	{
		ft_dprintf(2, "42sh: [CRITICAL] Malloc error\n");
		add_var(&g_shell->intern, "?", "1", READONLY_VAR);
		return (FAILURE);
	}
	run_type_selection(process, pipe);
	return (SUCCESS);
}

int			run_job(void *context, void *data)
{
	t_job		*job;
	t_process	*head;
	t_registry	*shell;

	if (data == NULL)
		return (FAILURE);
	shell = context;
	job = data;
	if (check_job(job, ft_atoi(get_var(shell->intern, "job_type"))) == FALSE)
		return (SUCCESS);
	job->state = RUNNING;
	if (job->processes->next == NULL)
	{
		head = job->processes->data;
		head->type |= IS_ALONE;
		run_process(head, 0);
	}
	else
		launch_pipeline(job->processes);
	return (waiter(job));
}
