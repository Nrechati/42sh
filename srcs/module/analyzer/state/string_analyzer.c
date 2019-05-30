/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 21:17:49 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:52:29 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	flush_string(t_resolution *resolve)
{
	int		index;
	t_token *token;

	resolve->state = P_STRING_FLUSH;
	if (ft_stcksize(&resolve->stack) == 0)
		return ;
	index = ft_stcksize(&resolve->stack);
	resolve->process.av = (char **)ft_malloc(sizeof(char *) * (index + 1));
	if (resolve->process.av == NULL)
		return ;
	resolve->process.av[index] = NULL;
	while (--index >= 0)
	{
		token = ft_stckpop(&resolve->stack);
		resolve->process.av[index] = token->data;
		ft_free(token);
	}
	resolve->special_case ^= VALID_PROCESS;
}

void	special_string_analyzer(t_resolution *resolve)
{
	resolve->state = P_SPSTRING;
	resolve->token.type = E_STRING;
	if ((resolve->token.data = string_expansion(resolve, resolve->token.data)))
		ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}

void	string_analyzer(t_resolution *resolve)
{
	resolve->state = P_STRING;
	ft_stckpush(&resolve->stack, &resolve->token, sizeof(t_token));
	get_token(resolve);
}
