/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_interpreter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 19:02:15 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/24 20:34:27 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

void	heredoc(t_registry *shell, t_redirect *redirect, t_action *action)
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

void	heredoc_trim(t_registry *shell, t_redirect *redirect, t_action *action)
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
			write_heredoc(shell->intern, &vector, fd[1], TRIM_ON);
	}
	vct_del(&vector);
}

void	io_heredoc(t_registry *shell, t_redirect *redirect, t_action *action)
{
	char		*delimiter;
	int			io_num;
	int			fd[2];
	t_vector	*vector;

	vector = NULL;
	delimiter = NULL;
	ft_asprintf(&delimiter, "%s\n", ((t_token *)action->data->data)->data);
	io_num = ft_atoi(((t_token *)action->data->next->data)->data);
	pipe(fd);
	while (sle(shell, &vector, SLE_PS3_PROMPT) == SUCCESS)
	{
		if (check_delimiter(&delimiter, &vector, fd[1]) == SUCCESS)
		{
			redirect->type |= FD_DUP;
			redirect->from = io_num;
			redirect->to = fd[0];
			return ;
		}
		else
			write_heredoc(shell->intern, &vector, fd[1], TRIM_OFF);
	}
	vct_del(&vector);
}

void	io_heredoc_trim(t_registry *shell, t_redirect *redirect
						, t_action *action)
{
	char		*delimiter;
	int			io_num;
	int			fd[2];
	t_vector	*vector;

	vector = NULL;
	delimiter = NULL;
	ft_asprintf(&delimiter, "%s\n", ((t_token *)action->data->data)->data);
	io_num = ft_atoi(((t_token *)action->data->next->data)->data);
	pipe(fd);
	while (sle(shell, &vector, SLE_PS3_PROMPT) == SUCCESS)
	{
		if (check_delimiter(&delimiter, &vector, fd[1]) == SUCCESS)
		{
			redirect->type |= FD_DUP;
			redirect->from = io_num;
			redirect->to = fd[0];
			return ;
		}
		else
			write_heredoc(shell->intern, &vector, fd[1], TRIM_ON);
	}
	vct_del(&vector);
}
