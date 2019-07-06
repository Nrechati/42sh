/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_interpreter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 21:23:29 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/07 00:57:23 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

t_list	*create_pipe(int to, int from, unsigned int pipe_type)
{
	t_list		*node;
	t_redirect	pipe;

	ft_bzero(&pipe, sizeof(t_redirect));
	pipe.to = to;
	pipe.from = from;
	pipe.type = pipe_type;
	node = ft_lstnew(&pipe, sizeof(t_redirect));
	return (node);
}

void	close_pipe(void *data)
{
	t_redirect	*redirect;

	redirect = data;
	if (redirect->type & FD_PIPE_IN)
	{
		if (redirect->to >= 3)
			close(redirect->to);
		if (redirect->from >= 3)
			close(redirect->from);
	}
}

int		setup_pipe(t_process *current, t_process *next, int pipe_fd[2])
{
	t_list		*pipe_node;

	if ((pipe_node = create_pipe(pipe_fd[1], pipe_fd[0], FD_PIPE_OUT)) == NULL)
		return (FAILURE);
	ft_lstadd(&current->pipe, pipe_node);
	if ((pipe_node = create_pipe(pipe_fd[0], pipe_fd[1], FD_PIPE_IN)) == NULL)
		return (FAILURE);
	ft_lstadd(&next->pipe, pipe_node);
	return (SUCCESS);
}

int8_t	launch_pipeline(t_list *process, uint8_t foreground)
{
	int			pipe_fd[2];

	pipe_fd[0] = 0;
	pipe_fd[1] = 0;
	if (process == NULL)
		return (SUCCESS);
	if (process->next)
	{
		if (pipe(pipe_fd) == FAILURE)
			return (FAILURE);
		if (setup_pipe(process->data, process->next->data, pipe_fd) == FAILURE)
			return (FAILURE);
	}
	run_process(process->data, foreground, pipe_fd[1]);
	launch_pipeline(process->next, foreground);
	pipe_fd[0] == 0 ? pipe_fd[0] : close(pipe_fd[0]);
	return (SUCCESS);
}
