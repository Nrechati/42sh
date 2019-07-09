/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 13:46:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 09:23:02 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

static int8_t	setup_builtin(t_process *process, uint8_t fg, uint8_t *std)
{
	(void)fg;
	if (process->type & IS_ALONE)
		return (ft_lstiter_ctx(process->redirects, std, builtin_redirect));
	else
		return (ft_lstiter_ctx(process->redirects, NULL, do_redirect));
}

int8_t			run_builtin(t_process *process, uint8_t foreground)
{
	char			*tty_name;
	uint8_t			std;
	t_builtin		builtin;
	int				status;

	std = 0;
	tty_name = ttyname(STDIN_FILENO);
	if (setup_builtin(process, foreground, &std) == FAILURE)
		return (TRUE);
	builtin = ft_hmap_getdata(&g_shell->hash.blt, process->av[0]);
	status = builtin(g_shell, process->av);
	if (process->type & IS_ALONE)
	{
		process->status = status;
		default_io(std, tty_name);
	}
	ft_lstiter(process->redirects, close_redirect);
	return (TRUE);
}

static void		run_type_selection(t_process *process, uint8_t foreground)
{
	if (process->type & IS_ASSIGN)
		process->completed = assign_intern(g_shell, &process->env);
	else if (process->av == NULL || process->av[0] == NULL)
		process->completed = 1;
	else if (process->type == (IS_ALONE | IS_BLT) && foreground == TRUE)
		process->completed = run_builtin(process, foreground);
	else
		process->completed = fork_process(process, foreground);
}

int				run_process(t_process *process, uint8_t foreground, int pipe)
{
	setup_redirect(process);
	if (process->type & (IS_DUP_FAILED | IS_CRITICAL | IS_OPEN_FAILED))
	{
		pipe ? close(pipe) : 0;
		add_var(&g_shell->intern, "?", "1", READONLY_VAR);
		return (process->completed = FAILURE);
	}
	if (expand_process(g_shell->intern, process) == FAILURE)
	{
		pipe ? close(pipe) : 0;
		add_var(&g_shell->intern, "?", "1", READONLY_VAR);
		process->completed = 1;
		return (FAILURE);
	}
	if (get_process_type(g_shell, process) == FAILURE)
	{
		pipe ? close(pipe) : 0;
		ft_dprintf(2, "42sh: [CRITICAL] Malloc error\n");
		add_var(&g_shell->intern, "?", "1", READONLY_VAR);
		return (FAILURE);
	}
	run_type_selection(process, foreground);
	pipe ? close(pipe) : 0;
	return (SUCCESS);
}

int				run_job(void *context, void *data)
{
	t_job		*job;
	t_process	*head;
	t_registry	*shell;
	uint8_t		foreground;

	if (data == NULL)
		return (FAILURE);
	shell = context;
	job = data;
	if (check_job(job, ft_atoi(get_var(shell->intern, "job_type"))) == FALSE)
		return (SUCCESS);
	foreground = job->type & GROUP_BG ? FALSE : TRUE;
	job->state = RUNNING;
	if (job->processes->next == NULL)
	{
		head = job->processes->data;
		head->type |= IS_ALONE;
		if (run_process(head, foreground, 0) == FAILURE)
			return (FAILURE);
	}
	else if (launch_pipeline(job->processes, foreground) == FAILURE)
		return (FAILURE);
	return (foreground == FALSE ? setup_background_job(job) : waiter(job));
}
