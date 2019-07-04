/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 22:20:11 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/04 14:16:52 by cempassi         ###   ########.fr       */
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

static void print_signaled(char *command, int signo)
{
	if (signo == SIGHUP)
		ft_dprintf(2, "42sh: %s: terminal hangup [1]\n", command);
	if (signo == SIGQUIT)
		ft_dprintf(2, "42sh: %s: Quit [3]\n", command);
	if (signo == SIGILL)
		ft_dprintf(2, "42sh: %s: Illegal instruction [4]\n", command);
	if (signo == SIGTRAP)
		ft_dprintf(2, "42sh: %s: Trap [5]\n", command);
	if (signo == SIGABRT)
		ft_dprintf(2, "42sh: %s: Abort [6]\n", command);
	if (signo == SIGEMT)
		ft_dprintf(2, "42sh: %s: EMT Trap [7]\n", command);
	if (signo == SIGFPE)
		ft_dprintf(2, "42sh: %s: floating point exception [8]\n", command);
	if (signo == SIGKILL)
		ft_dprintf(2, "42sh: %s: killed [9]\n", command);
	if (signo == SIGBUS)
		ft_dprintf(2, "42sh: %s: bus error [10]\n", command);
	if (signo == SIGSEGV)
		ft_dprintf(2, "42sh: %s: segmentation fault[11]\n", command);
	if (signo == SIGSYS)
		ft_dprintf(2, "42sh: %s: Bad system call [12]\n", command);
	if (signo == SIGALRM)
		ft_dprintf(2, "42sh: %s: Alarm clock [14]\n", command);
	if (signo == SIGTERM)
		ft_dprintf(2, "42sh: %s: Terminated [15]\n", command);
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
