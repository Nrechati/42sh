/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 10:31:56 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/19 12:38:59 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t		set_signame(char *sigtab[32])
{
	int		i;

	i = 0;
	sigtab[0] = ft_strdup("NOSIG");
	sigtab[1] = ft_strdup("SIGHUP");
	sigtab[2] = ft_strdup("SIGINT");
	sigtab[3] = ft_strdup("SIGQUIT");
	sigtab[4] = ft_strdup("SIGILL");
	sigtab[5] = ft_strdup("SIGTRAP");
	sigtab[6] = ft_strdup("SIGABRT");
	sigtab[7] = ft_strdup("SIGEMT");
	sigtab[8] = ft_strdup("SIGFPE");
	sigtab[9] = ft_strdup("SIGKILL");
	sigtab[10] = ft_strdup("SIGBUS");
	sigtab[11] = ft_strdup("SIGSEGV");
	sigtab[12] = ft_strdup("SIGSYS");
	sigtab[13] = ft_strdup("SIGPIPE");
	sigtab[14] = ft_strdup("SIGALRM");
	sigtab[15] = ft_strdup("SIGTERM");
	sigtab[16] = ft_strdup("SIGURG");
	sigtab[17] = ft_strdup("SIGSTOP");
	sigtab[18] = ft_strdup("SIGSTP");
	sigtab[19] = ft_strdup("SIGCONT");
	sigtab[20] = ft_strdup("SIGTTIN");
	sigtab[21] = ft_strdup("SIGTTOU");
	sigtab[22] = ft_strdup("SIGIO");
	sigtab[23] = ft_strdup("SIGXCPU");
	sigtab[24] = ft_strdup("SIGXFSZ");
	sigtab[25] = ft_strdup("SIGVTALRM");
	sigtab[26] = ft_strdup("SIGPROF");
	sigtab[27] = ft_strdup("SIGWINCH");
	sigtab[28] = ft_strdup("SIGINFO");
	sigtab[29] = ft_strdup("SIGINFO");
	sigtab[30] = ft_strdup("SIGUSR1");
	sigtab[31] = ft_strdup("SIGUSR2");
	while (i < 32)
	{
		if (sigtab[i] == NULL)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static void	update_pid(t_job *job, pid_t pid, int status, char *sigtab[32])
{
	t_list			*processes;
	t_process		*current;

	processes = job->processes;
	while (processes)
	{
		current = processes->data;
		if (current->pid == pid)
		{
			ft_printf("%s ended with status %d\n", current->av[0], status); //REWORK
			if (WIFEXITED(status))
			{
				if (status != 0)
				{
					job->state |= FAILED;
					current->completed = ERROR;
				}
				else
					current->completed = TRUE;
			}
			if (WIFSIGNALED(status))
			{
				ft_printf("%s terminated with status %d by %s\n"
						, current->av[0], status, sigtab[WTERMSIG(status)]);
				job->state |= FAILED;
				current->stopped = TRUE;
			}
			return ;
		}
		processes = processes->next;
	}
	return ;
}

static uint8_t	all_is_done(t_list *processes)
{
	t_process	*current;

	while (processes)
	{
		current = processes->data;
		if (current->completed == FALSE && current->stopped == FALSE)
			return (FALSE);
		processes = processes->next;
	}
	return (TRUE);
}

void			terminator(void *context, void *data)
{
	uint32_t	*signo;
	t_process	*process;

	signo = context;
	process = data;
	if (process->completed == FALSE)
		kill(process->pid, *signo);
	return ;
}

int8_t			waiter(t_job *job)
{
	int				status;
	pid_t			pid;
	static char		*sigtab[32];

	if (*sigtab == NULL)
		if (set_signame(sigtab) == FAILURE)
			return (FAILURE);
	while (all_is_done(job->processes) == FALSE)
	{
		if (job->state & KILLED)
			ft_lstiter_ctx(job->processes, &job->signo, terminator);
		else
		{
			status = 0;
			pid = wait(&status);
			if (pid)
				update_pid(job, pid, status , sigtab);
		}
	}
	if (job->state & KILLED)
		ft_printf("\x1b[33m\n [1]\tjob killed by : SIG%d\n\x1b[0m", job->signo);
	if ((!(job->state & FAILED)) && (!(job->state & FAILED)))
		job->state |= SUCCEDED;
	job->state = ENDED;
	return (SUCCESS);
}
