/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:56:23 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/02 16:03:17 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_redirection	*redirecter_init(void)
{
	static t_redirection	redirecter;

	redirecter[A_STDOUT_TRUNCATE_FILE] = stdout_truncate;
	redirecter[A_STDOUT_TRUNCATE_FILE_SPECIAL] = stdout_truncate_special;
	redirecter[A_STDOUT_APPEND_FILE] = stdout_append;
	redirecter[A_STDIN_READ_FILE] = stdin_readfile;
	redirecter[A_STDIN_READ_FD] = stdin_readfd;
	redirecter[A_IO_TRUNCATE_FILE] = io_truncate;
	redirecter[A_IO_APPEND_FILE] = io_append;
	redirecter[A_IO_READ_FILE] = io_readfile;
	redirecter[A_IO_READ_FD] = io_readfd;
	redirecter[A_DUP] = duplicate_fd;
	redirecter[A_CLOSE] = close_fd;
	redirecter[A_MOVE] = move_fd;
	redirecter[A_HEREDOC] = heredoc;
	redirecter[A_HEREDOC_TRIM] = heredoc_trim;
	redirecter[A_IO_HEREDOC] = io_heredoc;
	redirecter[A_IO_HEREDOC_TRIM] = io_heredoc_trim;
	return (&redirecter);
}

char			*get_filename(t_list *node)
{
	t_token		*token;
	char		*filename;

	token = node->data;
	if ((filename = expansion_pipeline(g_shell->intern, token->data)) == NULL)
		return (NULL);
	if (*filename == '\0')
		return (filename);
	if (filename[0] == '/' || ft_strnequ("./", filename, 2))
		return (filename);
	else
		return (filename);
}

int				get_io(t_list *node)
{
	t_token		*token;

	token = node->data;
	return (ft_atoi(token->data));
}

int				check_delimiter(char **delimiter, t_vector **vector, int fd)
{
	if (!(*vector) || ft_strequ((*vector)->buffer, *delimiter) == TRUE)
	{
		close(fd);
		ft_strdel(delimiter);
		vct_del(vector);
		return (SUCCESS);
	}
	return (FAILURE);
}

int				write_heredoc(t_list *intern_var, t_vector **vector, int fd
								, int trim)
{
	char		*string;
	int			index;

	index = 0;
	string = expansion_pipeline(intern_var, (*vector)->buffer);
	if (string)
	{
		while (trim == TRIM_ON && ft_strchr(" \t", string[index]))
			index++;
		ft_putstr_fd(string + index, fd);
		ft_strdel(&string);
		vct_del(vector);
	}
	return (0);
}

int		get_custom_fd(char **str, t_list *node)
{
	t_token		*token;
	int			action_type;
	char		*holder;

	token = node->data;
	if ((holder = expansion_pipeline(g_shell->intern, token->data)) == NULL)
		return (FAILURE);
	if (ft_strequ(holder, ""))
	{
		ft_dprintf(2, SH_GENERAL_ERROR "%s: ambiguous redirect\n", token->data);
		ft_strdel(&holder);
		return (-2);
	}
	if ((action_type = define_io_dup_move(token)) == A_AMBIGOUS_REDIRECT)
	{
		ft_dprintf(2, SH_GENERAL_ERROR "%s: ambiguous redirect\n", holder);
		ft_strdel(&holder);
		return (-2);
	}
	*str = holder;
	return (action_type);
}
