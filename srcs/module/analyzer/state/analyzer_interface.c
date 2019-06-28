/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_interface.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:01:44 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/27 23:10:05 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		check_token(t_resolution *resolve)
{
	if (resolve->token.type == E_SEMICOLON)
		return (0);
	if (resolve->token.type == E_PIPE)
		return (0);
	if (resolve->token.type == E_END)
		return (0);
	if (resolve->token.type == E_NEWLINE)
		return (0);
	return (1);
}

void	error_analyzer(t_resolution *resolve)
{
	if (resolve->valid == -2)
		ft_dprintf(2, "42sh: ambigous redirect");
	else
	{
		ft_dprintf(2, "42sh: analyze error near unexpected token `%s'\n",
				g_shell->grammar[resolve->token.type]);
	}
	resolve->state = P_ERROR;
	resolve->valid = -1;
	ft_strdel(&resolve->token.data);
	ft_stckdestroy(&resolve->stack, del_token);
	ft_stckdestroy(&resolve->tree_node, del_action);
	while (check_token(resolve))
	{
		get_token(resolve);
		ft_strdel(&resolve->token.data);
	}
}

void	stop_analyzer(t_resolution *resolve)
{
	t_action	action;

	resolve->state = P_STOP;
	if (resolve->valid == 1)
	{
		ft_bzero(&action, sizeof(t_action));
		if (resolve->token.type == E_DAND)
			action.type = A_DAND;
		else if (resolve->token.type == E_OR)
			action.type = A_OR;
		else if (resolve->token.type == E_SEMICOLON)
			action.type = A_END;
		else if (resolve->token.type == E_AND)
			action.type = A_AND;
		ft_stckpush(&resolve->tree_node, &action, sizeof(t_action));
		resolve->valid = 0;
	}
	get_token(resolve);
}

void	end_analyzer(t_resolution *resolve)
{
	t_action	action;

	resolve->state = P_END;
	if (resolve->valid == 1)
	{
		ft_bzero(&action, sizeof(t_action));
		action.type = A_END;
		ft_stckpush(&resolve->tree_node, &action, sizeof(t_action));
	}
	get_token(resolve);
}
