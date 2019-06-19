/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 21:33:53 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/19 21:39:04 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

void	default_io(const uint8_t std, char *tty_name)
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

void	set_process_pgid(void *context, void *data)
{
	t_job		*job;
	t_process	*process;

	job = context;
	process = data;
	process->pgid = &job->pgid;
	return ;
}

void	set_stopped(void *data)
{
	t_process	*process;

	process = data;
	process->stopped = TRUE;
	return ;
}

void	set_signaled(void *context, void *data)
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

int		get_failed_process(void *data, void *context)
{
	t_process	*current;

	(void)context;
	current = data;
	if (current->process_type & (IS_NOTFOUND | IS_OPEN_FAILED | IS_CRITICAL))
		return (TRUE);
	return (FALSE);
}
