/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_interpreter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 19:02:15 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/19 18:45:05 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

static int	write_heredoc(t_list *intern_var, t_vector **vector
						, int fd, __unused int trim)
{
	char		*string;

	string = expansion_pipeline(intern_var, &(*vector)->buffer);
	ft_putstr_fd(string, fd);
	ft_strdel(&string);
	vct_del(vector);
	return (0);
}

static int	check_delimiter(char **delimiter, t_vector **vector , int fd)
{
	if (ft_strequ((*vector)->buffer, *delimiter) == TRUE )
	{
		close(fd);
		ft_strdel(delimiter);
		vct_del(vector);
		return (SUCCESS);
	}
	return (FAILURE);
}

void		io_heredoc(t_registry *shell, t_redirect *redirect, t_action *action)
{
	char		*delimiter;
	int			fd[2];
	t_vector	*vector;

	vector = NULL;
	delimiter = NULL;
	ft_asprintf(&delimiter, "%s\n", ((t_token *)action->data->data)->data);
	pipe(fd);
	while (sle(shell, &vector, SLE_PS3_PROMPT) == SUCCESS)
	{
		if (check_delimiter(&delimiter, &vector, fd[1]) == SUCCESS)
		{
			redirect->type |= FD_DUP;
			redirect->from = STDIN_FILENO;
			redirect->to = fd[0];
			return ;
		}
		else
			write_heredoc(shell->intern, &vector, fd[1], TRIM_OFF);
	}
	vct_del(&vector);
}

void		heredoc(t_registry *shell, t_redirect *redirect, t_action *action)
{
	char		*delimiter;
	int			fd[2];
	t_vector	*vector;

	vector = NULL;
	delimiter = NULL;
	ft_asprintf(&delimiter, "%s\n", ((t_token *)action->data->data)->data);
	pipe(fd);
	while (sle(shell, &vector, SLE_PS3_PROMPT) == SUCCESS)
	{
		if (check_delimiter(&delimiter, &vector, fd[1]) == SUCCESS)
		{
			redirect->type |= FD_DUP;
			redirect->from = STDIN_FILENO;
			redirect->to = fd[0];
			return ;
		}
		else
			write_heredoc(shell->intern, &vector, fd[1], TRIM_OFF);
	}
	vct_del(&vector);
}
