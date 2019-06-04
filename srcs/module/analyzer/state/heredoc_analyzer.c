/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 21:48:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/04 19:05:07 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>
#include <unistd.h>

/*
static int	write_heredoc(char **line, int fd, t_resolution *resolve)
{
	int		trim;

	trim = 0;
	if (resolve->special_case & HERETRIM)
		trim = ft_strspn(*line, " \t");
	*line = variable_expansion(resolve, *line);
	ft_putendl_fd(*line + trim, fd);
	ft_strdel(line);
	return (0);
}

static int	check_delimiter(char **delimiter, char **line, int fd,
				t_resolution *resolve)
{
	if (ft_strequ(*line, *delimiter) == TRUE || *line[0] == 4)
	{
		close(fd);
		ft_putchar('\n');
		ft_strdel(delimiter);
		ft_strdel(line);
		resolve->special_case ^= HERETRIM;
		return (SUCCESS);
	}
	write_heredoc(line, fd, resolve);
	return (FAILURE);
}
*/
void		heredoc_delimiter(t_resolution *resolve)
{
	if (resolve->state == P_HEREDOC_REDIRECT)
		resolve->state = P_HEREDOC_DELIMITER;
	else
		resolve->state = P_IO_HEREDOC_DELIMITER;
	if ((g_shell->option.option & INTERACTIVE_OPT) == FALSE)
	{
		ft_dprintf(2, "21sh: Here documents only in interractive mode\n");
		ft_lstdel(&resolve->token_list, del_token);
		ft_strdel(&resolve->token.data);
		error_analyzer(resolve);
	}
	resolve->token.type = E_STRING;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}

void		io_heredoc_analyzer(t_resolution *resolve)
{
	char		*line;
	char		*delimiter;
	char		*io;
	int			fd[2];

	resolve->state = P_HEREDOC;
	pipe(fd);
	line = NULL;
	delimiter = pop_token_data(&resolve->stack);
	pop_token_type(&resolve->stack);
	io = pop_token_data(&resolve->stack);
	generate_filedesc(resolve, fd[0], ft_atoi(io), FD_DUP | FD_WRITE);
	ft_strdel(&io);
//	while (invoke_ps2prompt(g_shell, &line, INT_PS3) == SUCCESS)
//	{
//		if (check_delimiter(&delimiter, &line, fd[1], resolve) == SUCCESS)
//			return ;
//	}
	ft_strdel(&line);
	error_analyzer(resolve);
}

void		heredoc_analyzer(t_resolution *resolve)
{
	char		*line;
	char		*delimiter;
	int			fd[2];

	resolve->state = P_HEREDOC;
	line = NULL;
	pipe(fd);
	delimiter = pop_token_data(&resolve->stack);
	pop_token_data(&resolve->stack);
	generate_filedesc(resolve, fd[0], STDIN_FILENO, FD_DUP | FD_WRITE);
//	while (invoke_ps2prompt(g_shell, &line, INT_PS3) == SUCCESS)
//	{
//		if (check_delimiter(&delimiter, &line, fd[1], resolve) == SUCCESS)
//			return ;
//	}
	ft_strdel(&line);
	error_analyzer(resolve);
}
