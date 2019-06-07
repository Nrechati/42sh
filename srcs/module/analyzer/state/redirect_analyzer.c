/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:57:46 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/06 18:33:24 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>
#include <unistd.h>

void	activate_piping(void *data)
{
	t_redirect *fd;

	fd = data;
	fd->action |= FD_PIPE;
}

void	flush_redirect_and(t_resolution *resolve)
{
	/*char			*filedesc;
	int				fd;
	unsigned int	action;
	t_type			type;
*/
	resolve->state = P_REDIRECT_FLUSH_AND;
	/*
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
		*/
}

void	flush_redirect(t_resolution *resolve)
{
	char	*filename;

	resolve->state = P_REDIRECT_FLUSH;
	ft_strdel(&filename);
}

void	redirect_and_analyzer(t_resolution *resolve)
{
	resolve->state = P_REDIRECT_AND;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}

void	redirect_analyzer(t_resolution *resolve)
{
	resolve->state = P_REDIRECT;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}
