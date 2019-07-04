/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 22:20:11 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/04 14:31:52 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void	stopped_process(t_job *job, int status)
{
	job->state = STOPPED;
	job->signo = WSTOPSIG(status);
	mark_job_as_stopped(job);
	g_shell->active_jobs++;
	job->id = (g_shell->active_jobs);
	jobctl(g_shell, job, JOBCTL_PUTINBG);
}

static void	exited_process(t_process *current, int status)
{
	char		*exit_status;

	exit_status = ft_itoa((uint8_t)WEXITSTATUS(status));
	if (WEXITSTATUS(status) != 0)
		current->completed = ERROR;
	else
		current->completed = TRUE;
	add_var(&g_shell->intern, "?", exit_status, READONLY_VAR);
	ft_strdel(&exit_status);
}

static void	print_signaled(char *command, int signo)
{
	static char			*signal_string[16] = { NULL, "terminal hangup", NULL
											, "Quit"
											, "Illegal instruction", "Trap"
											, "Abort", "EMT Trap"
											, "Floating point exception"
											, "killed", "bus error"
											, "segmentation fault"
											, "Bad system call"
											, NULL
											, "Alarm clock"
											, "Terminated"};

	if (signo != 2 && signo != 13 && signo >= 1 && signo <= 15)
		ft_dprintf(2, "42sh: %s: %s [%d]\n"
				, command, signal_string[signo], signo);
}

static void	signaled_process(t_job *job, int status)
{
	int			signo;
	char		*exit_status;
	char		*command;

	signo = WTERMSIG(status);
	command = get_var(g_shell->intern, "_input");
	print_signaled(command, signo);
	if (signo == 2 || signo == 3)
		sigstop_exec(signo);
	exit_status = ft_itoa((uint8_t)(signo + 128));
	mark_job_as_stopped(job);
	add_var(&g_shell->intern, "?", exit_status, READONLY_VAR);
	ft_strdel(&exit_status);
}

void		set_status(t_job *job, t_process *current, int status)
{
	if (WIFSTOPPED(status))
		stopped_process(job, status);
	if (WIFEXITED(status))
		exited_process(current, status);
	if (WIFSIGNALED(status))
		signaled_process(job, status);
}
