/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_interpreter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 21:23:29 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/12 16:17:00 by cempassi         ###   ########.fr       */
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

int8_t	setup_pipe(t_list *processess)
{
	int			pipe_fd[2];
	t_list		*pipe_node;
	t_process	*current;
	t_process	*next;

	if (processess->next == NULL)
		return (SUCCESS);
	current = processess->data;
	next = processess->next->data;
	if (pipe(pipe_fd) == FAILURE)
		return (FAILURE);
	if ((pipe_node = create_pipe(pipe_fd[1], pipe_fd[0], FD_PIPE_OUT)) == NULL)
		return (FAILURE);
	ft_lstadd(&current->redirects, pipe_node);
	if ((pipe_node = create_pipe(pipe_fd[0], pipe_fd[1], FD_PIPE_IN)) == NULL)
		return (FAILURE);
	ft_lstadd(&next->redirects, pipe_node);
	return (setup_pipe(processess->next));
}
