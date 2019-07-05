/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 13:46:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/05 14:23:37 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void	setup_builtin(t_process *process, uint8_t fg, uint8_t *std)
{
	if (fg == TRUE)
	{
		if (tcgetpgrp(STDOUT_FILENO) != *process->pgid)
			tcsetpgrp(STDOUT_FILENO, *process->pgid);
	}
	if (process->type & IS_ALONE)
		ft_lstiter_ctx(process->redirects, std, builtin_redirect);
	else
		ft_lstiter_ctx(process->redirects, NULL, do_redirect);
}

void		run_builtin(t_process *process, uint8_t foreground)
{
	char			*tty_name;
	uint8_t			std;
	t_builtin		builtin;

	std = 0;
	tty_name = ttyname(STDIN_FILENO);
	setup_builtin(process, foreground, &std);
	close(STDIN_FILENO);
	std |= CLOSED_STDIN;
	builtin = ft_hmap_getdata(&g_shell->hash.blt, process->av[0]);
	process->status = builtin(g_shell, process->av);
	if (process->type & IS_ALONE)
	{
		default_io(std, tty_name);
		process->completed = 1;
	}
	ft_lstiter(process->redirects, close_redirect);
	return ;
}

static void	run_type_selection(t_process *process, uint8_t foreground)
{
	if (process->type & IS_ASSIGN)
		process->completed = assign_intern(g_shell, &process->env);
	else if (process->type == (IS_ALONE | IS_BLT) && foreground == TRUE)
		run_builtin(process, foreground);
	else
		fork_process(process, foreground);
}

int			run_process(t_process *process, uint8_t foreground)
{
	setup_redirect(process);
	if (process->type & (IS_DUP_FAILED | IS_CRITICAL | IS_OPEN_FAILED))
	{
		add_var(&g_shell->intern, "?", "1", READONLY_VAR);
		return (process->completed = FAILURE);
	}
	if (expand_process(g_shell->intern, process) == FAILURE)
	{
		process->type = IS_EXP_ERROR;
		return (FAILURE);
	}
	if (get_process_type(g_shell, process) == FAILURE)
	{
		ft_dprintf(2, "42sh: [CRITICAL] Malloc error\n");
		add_var(&g_shell->intern, "?", "1", READONLY_VAR);
		return (FAILURE);
	}
	run_type_selection(process, foreground);
	return (SUCCESS);
}

int			run_job(void *context, void *data)
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
		run_process(head, foreground);
	}
	else
		launch_pipeline(job->processes, foreground);
	return (foreground == FALSE ? setup_background_job(job) : waiter(job));
}
