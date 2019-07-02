/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:06:45 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/02 20:20:05 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	valid_heredoc_setup(t_redirect *redirect, int from, int to)
{
	redirect->type |= FD_REDIRECT;
	redirect->from = from;
	redirect->to = to;
}

int		check_delimiter(char **delimiter, t_vector **vector, int fd)
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

int		write_heredoc(t_vector **vector, int fd, int trim)
{
	char		*string;
	int			index;

	index = 0;
	string = expansion_pipeline(g_shell->intern, (*vector)->buffer);
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
