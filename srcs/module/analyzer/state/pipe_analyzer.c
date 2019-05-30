/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_analyzer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:57:46 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:52:29 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>
#include <unistd.h>

void	pipe_analyzer(t_resolution *resolve)
{
	t_list		*node;
	int			fd[2];

	resolve->state = pipe(fd) ? P_ERROR : P_PIPE;
	resolve->special_case ^= VALID_PROCESS;
	if (resolve->state == P_ERROR)
		return ;
	if (resolve->special_case & NO_PIPE)
		close(fd[1]);
	else
	{
		generate_filedesc(resolve, STDIN_FILENO, fd[0], FD_CLOSE);
		generate_filedesc(resolve, fd[1], STDOUT_FILENO
				, FD_DUP | FD_WRITE | FD_PIPE);
	}
	node = ft_lstnew(&resolve->process, sizeof(t_process));
	ft_lstaddback(&resolve->job.process_list, node);
	init_process(&resolve->process);
	generate_filedesc(resolve, STDOUT_FILENO, fd[1], FD_CLOSE);
	generate_filedesc(resolve, fd[0], STDIN_FILENO,
						FD_DUP | FD_WRITE | FD_PIPE);
	get_token(resolve);
}
