/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 22:20:11 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/05 14:04:19 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void	exited_process(t_process *current, int status)
{
	current->status = ((uint8_t)WEXITSTATUS(status));
	if (WEXITSTATUS(status) != 0)
		current->completed = ERROR;
	else
		current->completed = TRUE;
}

static int	set_signal_status(void *context, void *data)
{
	uint8_t		status;
	t_process	*current;

	status = *((uint8_t*)context);
	current = data;
	status += 128;
	current->status = status;
	return (SUCCESS);
}

static void	signaled_process(t_job *job, int status)
{
	int			signo;
	char		*command;

	signo = WTERMSIG(status);
	if (signo != SIGPIPE)
		ft_lstiter_ctx(job->processes, &signo, set_signal_status);
	command = get_var(g_shell->intern, "_input");
	print_signaled(command, signo);
	if (signo == SIGINT || signo == SIGQUIT)
		sigstop_exec(signo);
	mark_job_as_stopped(job);
}

void		set_status(t_job *job, t_process *current, int status)
{
	if (WIFEXITED(status))
		exited_process(current, status);
	if (WIFSIGNALED(status))
		signaled_process(job, status);
}
