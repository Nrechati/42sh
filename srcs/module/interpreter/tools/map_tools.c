/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 21:33:53 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/20 11:13:12 by nrechati         ###   ########.fr       */
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