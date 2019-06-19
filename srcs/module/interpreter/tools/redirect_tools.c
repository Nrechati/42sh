/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:56:23 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/19 21:51:03 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_redirection	*redirecter_init(void)
{
	static t_redirection	redirecter;

	redirecter[A_STDOUT_TRUNCATE_FILE] = stdout_truncate;
	redirecter[A_STDOUT_APPEND_FILE] = stdout_append;
	redirecter[A_STDIN_READ_FILE] = stdin_readfile;
	redirecter[A_IO_TRUNCATE_FILE] = io_truncate;
	redirecter[A_IO_APPEND_FILE] = io_append;
	redirecter[A_IO_READ_FILE] = io_readfile;
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
	filename = NULL;
	if (token->data[0] == '/' || ft_strnequ("./", token->data, 2))
		filename = ft_strdup(token->data);
	else
		ft_asprintf(&filename, "./%s", token->data);
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
	if (ft_strequ((*vector)->buffer, *delimiter) == TRUE)
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
	string = expansion_pipeline(intern_var, &(*vector)->buffer);
	while (trim == TRIM_ON && ft_strchr(" \t", string[index]))
		index++;
	ft_putstr_fd(string + index, fd);
	ft_strdel(&string);
	vct_del(vector);
	return (0);
}
