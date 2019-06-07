/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect_analyzer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 04:42:30 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/06 18:20:50 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

void	io_redirect_flush(t_resolution *resolve)
{
	int			action;

	action = 0;
	resolve->state = P_IO_FLUSH;
}

void	io_and_redirect_flush(t_resolution *resolve)
{
	unsigned int	action;

	action = 0;
	resolve->state = P_IO_FLUSH_AND;
}

void	io_redirect_analyzer(t_resolution *resolve)
{
	resolve->state = P_IO_REDIRECT;
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
