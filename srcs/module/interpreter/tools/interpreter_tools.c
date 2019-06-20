/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 10:30:03 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/20 10:34:01 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

int			get_failed_process(void *data, void *context)
{
	t_process	*current;

	(void)context;
	current = data;
	if (current->process_type & (IS_NOTFOUND | IS_OPEN_FAILED | IS_CRITICAL))
		return (TRUE);
	return (FALSE);
}

void		re_open_std(const uint8_t std, char *tty_name)
{
	int		fd;

	fd = open(tty_name, O_RDWR);
	if (std & CLOSED_STDIN)
		dup2(fd, STDIN_FILENO);
	if (std & CLOSED_STDOUT)
		dup2(fd, STDOUT_FILENO);
	if (std & CLOSED_STDERR)
		dup2(fd, STDERR_FILENO);
	if (fd >= 3)
		close(fd);
	return ;
}

uint8_t		do_i_run(t_registry *shell, int job_type)
{
	char	*last_status;

	last_status = get_var(shell->intern, "?");
	if (ft_atoi(last_status) > 128)
		return (FALSE);
	else if (job_type & GROUP_AND)
	{
		if (ft_strequ(last_status, "0") == FALSE)
			return (FALSE);
	}
	else if (job_type & GROUP_OR)
	{
		if (ft_strequ(last_status, "0") == TRUE)
			return (FALSE);
	}
	return (TRUE);
}

void		set_stopped(void *data)
{
	t_process	*process;

	process = data;
	process->stopped = TRUE;
	return ;
}

void		set_signaled(void *context, void *data)
{
	t_job		*job;
	uint32_t	*signo;

	job = data;
	signo = context;
	job->state |= KILLED;
	job->signo = *signo;
	ft_lstiter(job->processes, set_stopped);
	return ;
}