/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:57:46 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/04 17:51:23 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>
#include <unistd.h>

void	activate_piping(void *data)
{
	t_filedesc *fd;

	fd = data;
	fd->action |= FD_PIPE;
}

void	flush_redirect_and(t_resolution *resolve)
{
	char			*filedesc;
	int				fd;
	unsigned int	action;
	t_type			type;

	resolve->state = P_REDIRECT_FLUSH_AND;
	action = 0;
	filedesc = pop_token_data(&resolve->stack);
	fd = ft_atoi(filedesc);
	ft_strdel(&filedesc);
	type = pop_token_type(&resolve->stack);
	action |= resolve->special_case & TO_CLOSE ? FD_CLOSE : FD_DUP;
	resolve->special_case ^= TO_CLOSE;
	if (type == E_LESSAND)
		generate_filedesc(resolve, fd, STDIN_FILENO, action | FD_WRITE);
	else
		generate_filedesc(resolve, fd, STDOUT_FILENO, action | FD_WRITE);
}

void	flush_redirect(t_resolution *resolve)
{
	char	*filename;
	t_type	type;
	int		fd;

	resolve->state = P_REDIRECT_FLUSH;
	filename = pop_token_data(&resolve->stack);
	type = pop_token_type(&resolve->stack);
	if ((fd = open(filename, resolve->oflags, 0644)) < 0)
	{
		ft_dprintf(2, "21sh: %s: No such file\n", filename);
		error_analyzer(resolve);
	}
	else if (type == E_LESS || type == E_LESSAND)
		generate_filedesc(resolve, fd, STDIN_FILENO, FD_DUP | FD_WRITE);
	else
	{
		if (type == E_GREATAND || type == E_ANDDGREAT)
			generate_filedesc(resolve, fd, STDERR_FILENO, FD_DUP | FD_WRITE);
		else if (type == E_ANDGREAT)
			generate_filedesc(resolve, fd, STDERR_FILENO, FD_DUP | FD_WRITE);
		generate_filedesc(resolve, fd, STDOUT_FILENO, FD_DUP | FD_WRITE);
	}
	resolve->special_case ^= NO_PIPE;
	ft_strdel(&filename);
}

void	redirect_and_analyzer(t_resolution *resolve)
{
	resolve->state = P_REDIRECT_AND;
	if (resolve->token.type == E_GREATAND)
		resolve->oflags = O_RDWR + O_CREAT + O_TRUNC;
	else if (resolve->token.type == E_LESSAND)
		resolve->oflags = O_RDONLY;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}

void	redirect_analyzer(t_resolution *resolve)
{
	resolve->state = P_REDIRECT;
	if (resolve->token.type == E_GREAT)
		resolve->oflags = O_RDWR + O_CREAT + O_TRUNC;
	else if (resolve->token.type == E_DGREAT
			|| resolve->token.type == E_ANDDGREAT)
		resolve->oflags = O_RDWR + O_CREAT + O_APPEND;
	else if (resolve->token.type == E_LESS)
		resolve->oflags = O_RDONLY;
	else if (resolve->token.type == E_DLESSDASH
			|| resolve->token.type == E_DLESS)
		resolve->state = P_HEREDOC_REDIRECT;
	if (resolve->token.type == E_DLESSDASH)
		resolve->special_case ^= HERETRIM;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}
