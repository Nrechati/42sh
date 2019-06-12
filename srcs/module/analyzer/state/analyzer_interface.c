/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_interface.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:01:44 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/12 17:29:25 by cempassi         ###   ########.fr       */
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
	resolve->state = P_ERROR;
	resolve->valid = -1;
	ft_dprintf(2, "42sh: analyze error near unexpected token `%s'\n",
						g_grammar[resolve->token.type]);
	ft_strdel(&resolve->token.data);
	while (check_token(resolve))
	{
		get_token(resolve);
		ft_strdel(&resolve->token.data);
	}
	resolve->token.type = E_DEFAULT;
}

void	separator_analyzer(t_resolution *resolve)
{
	resolve->state = P_SEPARATOR;
}

void	stop_analyzer(t_resolution *resolve)
{
	t_action	action;

	resolve->state = P_STOP;
	ft_bzero(&action, sizeof(t_action));
	action.type = A_END;
	ft_stckpush(&resolve->tree_node, &action, sizeof(t_action));
	resolve->valid = 1;
	get_token(resolve);
}

void	end_analyzer(t_resolution *resolve)
{
	t_action	action;

	resolve->state = P_END;
	ft_bzero(&action, sizeof(t_action));
	action.type = A_END;
	ft_stckpush(&resolve->tree_node, &action, sizeof(t_action));
	resolve->valid = 1;
	get_token(resolve);
}
