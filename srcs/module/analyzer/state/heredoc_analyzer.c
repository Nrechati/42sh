/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 21:48:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/18 15:05:46 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>
#include <unistd.h>

/*
>>>>>>> analyzer
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
		ft_dprintf(2, "42sh: Here documents only in interractive mode\n");
		ft_lstdel(&resolve->tokens, del_token);
		ft_strdel(&resolve->token.data);
		error_analyzer(resolve);
	}
	resolve->token.type = E_STRING;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}

void		io_heredoc_analyzer(t_resolution *resolve)
{
	t_list			*node;
	t_action		action;
	enum e_type		type;

	resolve->state = P_IO_HEREDOC;
	ft_bzero(&action, sizeof(t_action));
	node = ft_stckpopnode(&resolve->stack);
	ft_lstaddback(&action.data, node);
	node = ft_stckpopnode(&resolve->stack);
	type = ((t_token *)node->data)->type;
	if (type == E_DLESS)
		action.type = A_IO_HEREDOC;
	else if (type == E_DLESSDASH)
		action.type = A_IO_HEREDOC_TRIM;
	ft_lstdelone(&node, NULL);
	node = ft_stckpopnode(&resolve->stack);
	ft_lstaddback(&action.data, node);
	node = ft_lstnew(&action, sizeof(t_action));
	ft_stckpush(&resolve->tree_node, &action, sizeof(t_action));

}

void		heredoc_analyzer(t_resolution *resolve)
{
	t_list			*node;
	t_action		action;
	enum e_type		type;

	resolve->state = P_HEREDOC;
	ft_bzero(&action, sizeof(t_action));
	node = ft_stckpopnode(&resolve->stack);
	ft_lstaddback(&action.data, node);
	node = ft_stckpopnode(&resolve->stack);
	type = ((t_token *)node->data)->type;
	if (type == E_DLESS)
		action.type = A_HEREDOC;
	else if (type == E_DLESSDASH)
		action.type = A_HEREDOC_TRIM;
	ft_lstdelone(&node, NULL);
	node = ft_lstnew(&action, sizeof(t_action));
	ft_stckpush(&resolve->tree_node, &action, sizeof(t_action));
}
