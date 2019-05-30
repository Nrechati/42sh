/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 04:47:14 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:52:29 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	filename_analyzer(t_resolution *resolve)
{
	if (resolve->token.type == E_SPSTRING)
		resolve->token.data = string_expansion(resolve, resolve->token.data);
	if (resolve->state == P_IO_REDIRECT)
		resolve->state = P_IO_FILENAME;
	else if (resolve->token.type == E_SPSTRING)
		resolve->state = P_SPFILENAME;
	else
		resolve->state = P_FILENAME;
	check_filename(resolve);
	get_token(resolve);
}

void	dup_move_analyzer(t_resolution *resolve)
{
	t_token *token;

	if ((resolve->token.data = string_expansion(resolve, resolve->token.data)))
	{
		if (is_ionumber(resolve, resolve->token.data))
			ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
		else if ((token = ft_stcktop(&resolve->stack))->type == E_LESSAND)
		{
			ft_dprintf(2, "21sh: %s: ambigous redirect", resolve->token.data);
			error_analyzer(resolve);
		}
		else
		{
			resolve->state = P_FILENAME;
			ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
		}
		get_token(resolve);
	}
	else
	{
		ft_strdel(&resolve->token.data);
		error_analyzer(resolve);
	}
}

void	io_dup_move_analyzer(t_resolution *resolve)
{
	resolve->token.type = E_STRING;
	if ((resolve->token.data = string_expansion(resolve, resolve->token.data)))
	{
		if (is_ionumber(resolve, resolve->token.data))
			ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
		else
		{
			error_analyzer(resolve);
			ft_strdel(&resolve->token.data);
		}
		get_token(resolve);
	}
	else
	{
		ft_strdel(&resolve->token.data);
		error_analyzer(resolve);
	}
}
