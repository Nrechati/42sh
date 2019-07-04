/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 17:37:26 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/04 01:20:42 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		setup_builtin(t_process *process, uint8_t fg, uint8_t *std)
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
	char			*status;
	uint8_t			std;
	t_builtin		builtin;

	std = 0;
	setup_builtin(process, foreground, &std);
	tty_name = ttyname(STDIN_FILENO);
	builtin = ft_hmap_getdata(&g_shell->hash.blt, process->av[0]);
	process->status = builtin(g_shell, process->av);
	status = ft_itoa(process->status);
	if (process->type & IS_ALONE)
		default_io(std, tty_name);
	ft_lstiter(process->redirects, close_redirect);
	add_var(&g_shell->intern, "?", status, READONLY_VAR);
	process->completed = 1;
	ft_strdel(&status);
	return ;
}

int			run_process(t_process *process, uint8_t foreground)
{
	if (process->type & (IS_DUP_FAILED | IS_CRITICAL | IS_OPEN_FAILED))
		return (process->completed = FAILURE);
	if (expand_process(g_shell->intern, process) == FAILURE)
	{
		process->type = IS_EXP_ERROR;
		return (FAILURE);
	}
	if (get_process_type(g_shell, process) == FAILURE)
	{
		ft_dprintf(2, "42sh: [CRITICAL] Mallox error\n");
		return (FAILURE);
	}
	if (process->type & IS_ASSIGN)
		process->completed = assign_intern(g_shell, &process->env);
	else if (process->type == (IS_ALONE | IS_BLT) && foreground == TRUE)
		run_builtin(process, foreground);
	else
		fork_process(process, foreground);
	return (SUCCESS);
}

static int	run_job(void *context, void *data)
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
	if (foreground == TRUE)
		return (waiter(job));
	return (SUCCESS);
}

int8_t		interpreter(t_registry *shell, t_list **cmd_group)
{
	t_list		*job_lst;
	char		*input;

	ptr_to_job_lst(&job_lst, SET_ADDR);
	job_lst = ft_lstmap(*cmd_group, shell, group_to_job, del_group);
	ft_lstdel(cmd_group, del_group);
	if ((input = get_var(g_shell->intern, "_input")))
		history(g_shell, input, ADD_ENTRY);
	load_signal_profile(EXEC_PROFILE);
	ft_lstiter_ctx(job_lst, shell, run_job);
	add_var(&shell->intern, "job_type", "0", READONLY_VAR);
	ft_lstdel(&job_lst, del_job);
	shell->sigint = 0;
	ptr_to_job_lst(NULL, SET_ADDR);
	return (SUCCESS);
}
