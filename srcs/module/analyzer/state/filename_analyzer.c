/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 04:47:14 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/03 00:57:38 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	filename_analyzer(t_analyze *analyze)
{
	if (analyze->state == P_IO_REDIRECT)
		analyze->state = P_IO_FILENAME;
	else
		analyze->state = P_FILENAME;
	ft_stckpush(&analyze->stack, &analyze->token, sizeof(t_token));
	get_token(analyze);
}

void	dup_move_analyzer(t_analyze *analyze)
{
	analyze->state = P_DUP_MOVE;
	ft_stckpush(&analyze->stack, &analyze->token, sizeof(t_token));
	get_token(analyze);
}

void	io_dup_move_analyzer(t_analyze *analyze)
{
	analyze->state = P_IO_DUP_MOVE;
	ft_stckpush(&analyze->stack, &analyze->token, sizeof(t_token));
	get_token(analyze);
}
