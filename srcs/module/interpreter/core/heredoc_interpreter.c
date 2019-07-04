/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_interpreter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 19:02:15 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/04 15:40:44 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

char	*get_heredoc_delim(char *data)
{
	char		*delimiter;
	int			i;

	i = 0;
	delimiter = NULL;
	while (data[i] != '\0')
	{
		if (data[i] == '\n')
			delete_character(data + i);
		++i;
	}
	quote_removal(data);
	ft_asprintf(&delimiter, "%s\n", data);
	return (delimiter);
}

void	heredoc(t_redirect *redirect, t_action *action)
{
	char		*delimiter;
	int			fd[2];
	t_vector	*vector;

	if ((g_shell->option.option & INTERACTIVE_OPT) == FALSE)
		return ;
	vector = NULL;
	delimiter = get_heredoc_delim(((t_token *)action->data->data)->data);
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
	delimiter = get_heredoc_delim(((t_token *)action->data->data)->data);
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
	delimiter = get_heredoc_delim(((t_token *)action->data->data)->data);
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
	delimiter = get_heredoc_delim(((t_token *)action->data->data)->data);
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
