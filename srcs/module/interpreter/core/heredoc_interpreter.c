/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_interpreter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 19:02:15 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/03 18:43:40 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

void	heredoc(t_redirect *redirect, t_action *action)
{
	char		*delimiter;
	int			fd[2];
	t_vector	*vector;

	if ((g_shell->option.option & INTERACTIVE_OPT) == FALSE)
		return ;
	vector = NULL;
	delimiter = NULL;
	ft_asprintf(&delimiter, "%s\n", ((t_token *)action->data->data)->data);
	pipe(fd);
	while (sle(g_shell, &vector, SLE_PS3_PROMPT) == SUCCESS)
	{
		if (check_delimiter(&delimiter, &vector, fd[1]) == SUCCESS)
			return (valid_heredoc_setup(redirect, STDIN_FILENO, fd[0]));
		else
			write_heredoc(&vector, fd[1], TRIM_OFF);
	}
	close(fd[1]);
	return (valid_heredoc_setup(redirect, STDIN_FILENO, fd[0]));
}

void	heredoc_trim(t_redirect *redirect, t_action *action)
{
	char		*delimiter;
	int			fd[2];
	t_vector	*vector;

	if ((g_shell->option.option & INTERACTIVE_OPT) == FALSE)
		return ;
	vector = NULL;
	delimiter = NULL;
	ft_asprintf(&delimiter, "%s\n", ((t_token *)action->data->data)->data);
	pipe(fd);
	while (sle(g_shell, &vector, SLE_PS3_PROMPT) == SUCCESS)
	{
		if (check_delimiter(&delimiter, &vector, fd[1]) == SUCCESS)
			return (valid_heredoc_setup(redirect, STDIN_FILENO, fd[0]));
		else
			write_heredoc(&vector, fd[1], TRIM_ON);
	}
	close(fd[1]);
	return (valid_heredoc_setup(redirect, STDIN_FILENO, fd[0]));
}

void	io_heredoc(t_redirect *redirect, t_action *action)
{
	char		*delimiter;
	int			io_num;
	int			fd[2];
	t_vector	*vector;

	if ((g_shell->option.option & INTERACTIVE_OPT) == FALSE)
		return ;
	vector = NULL;
	delimiter = NULL;
	ft_asprintf(&delimiter, "%s\n", ((t_token *)action->data->data)->data);
	io_num = ft_atoi(((t_token *)action->data->next->data)->data);
	pipe(fd);
	while (sle(g_shell, &vector, SLE_PS3_PROMPT) == SUCCESS)
	{
		if (check_delimiter(&delimiter, &vector, fd[1]) == SUCCESS)
			return (valid_heredoc_setup(redirect, io_num, fd[0]));
		else
			write_heredoc(&vector, fd[1], TRIM_OFF);
	}
	close(fd[1]);
	return (valid_heredoc_setup(redirect, io_num, fd[0]));
}

void	io_heredoc_trim(t_redirect *redirect, t_action *action)
{
	char		*delimiter;
	int			io_num;
	int			fd[2];
	t_vector	*vector;

	if ((g_shell->option.option & INTERACTIVE_OPT) == FALSE)
		return ;
	vector = NULL;
	delimiter = NULL;
	ft_asprintf(&delimiter, "%s\n", ((t_token *)action->data->data)->data);
	io_num = ft_atoi(((t_token *)action->data->next->data)->data);
	pipe(fd);
	while (sle(g_shell, &vector, SLE_PS3_PROMPT) == SUCCESS)
	{
		if (check_delimiter(&delimiter, &vector, fd[1]) == SUCCESS)
			return (valid_heredoc_setup(redirect, io_num, fd[0]));
		else
			write_heredoc(&vector, fd[1], TRIM_ON);
	}
	close(fd[1]);
	return (valid_heredoc_setup(redirect, io_num, fd[0]));
}
