/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect_analyzer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 04:42:30 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 19:02:24 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

void	io_redirect_flush(t_resolution *resolve)
{
	char		*filename;
	char		*io;
	int			fd;
	int			action;

	action = 0;
	resolve->state = P_IO_FLUSH;
	filename = pop_token_data(&resolve->stack);
	pop_token_type(&resolve->stack);
	io = pop_token_data(&resolve->stack);
	action |= FD_WRITE | FD_DUP;
	if ((fd = open(filename, resolve->oflags, 0644)) < 0)
		error_analyzer(resolve);
	else
		generate_filedesc(resolve, fd, ft_atoi(io), action);
	ft_strdel(&io);
	ft_strdel(&filename);
}

void	io_and_redirect_flush(t_resolution *resolve)
{
	char			*fd;
	char			*io;
	unsigned int	action;

	action = 0;
	resolve->state = P_IO_FLUSH_AND;
	fd = pop_token_data(&resolve->stack);
	pop_token_type(&resolve->stack);
	io = pop_token_data(&resolve->stack);
	action |= resolve->special_case & TO_CLOSE ? FD_CLOSE : FD_DUP;
	generate_filedesc(resolve, ft_atoi(fd), ft_atoi(io), action | FD_WRITE);
	ft_strdel(&fd);
	ft_strdel(&io);
}

void	io_redirect_analyzer(t_resolution *resolve)
{
	resolve->state = P_IO_REDIRECT;
	if (resolve->token.type == E_GREAT)
		resolve->oflags = O_RDWR + O_CREAT + O_TRUNC + O_CLOEXEC;
	else if (resolve->token.type == E_DGREAT)
		resolve->oflags = O_RDWR + O_CREAT + O_APPEND + O_CLOEXEC;
	else if (resolve->token.type == E_LESS)
		resolve->oflags = O_RDONLY + O_CLOEXEC;
	else if (resolve->token.type == E_DLESS
			|| resolve->token.type == E_DLESSDASH)
		resolve->state = P_IO_HEREDOC_REDIRECT;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}

void	io_redirect_and_analyzer(t_resolution *resolve)
{
	resolve->state = P_IO_REDIRECT_AND;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}

void	io_analyzer(t_resolution *resolve)
{
	resolve->state = P_IO;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}
