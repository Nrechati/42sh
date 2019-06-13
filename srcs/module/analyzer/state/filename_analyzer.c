/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 04:47:14 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/13 00:51:26 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	filename_analyzer(t_resolution *resolve)
{
	if (resolve->state == P_IO_REDIRECT)
		resolve->state = P_IO_FILENAME;
	else if (resolve->token.type == E_SPSTRING)
		resolve->state = P_SPFILENAME;
	else
		resolve->state = P_FILENAME;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
//	check_filename(resolve);
	get_token(resolve);
}

void	dup_move_analyzer(t_resolution *resolve)
{
	resolve->state = P_DUP_MOVE;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}

void	io_dup_move_analyzer(t_resolution *resolve)
{
	resolve->state = P_IO_DUP_MOVE;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}
