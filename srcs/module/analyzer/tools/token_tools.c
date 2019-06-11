/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 10:03:01 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/11 10:03:45 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	*pop_token_data(t_stack *stack)
{
	t_token *token;
	char	*data;

	token = ft_stckpop(stack);
	data = token->data;
	ft_free(token);
	return (data);
}

t_type	pop_token_type(t_stack *stack)
{
	t_token		*token;
	t_type		type;

	token = ft_stckpop(stack);
	type = token->type;
	ft_free(token);
	return (type);
}

void	get_token(t_resolution *resolve)
{
	t_list		*node;

	if (resolve->tokens == NULL)
		return ;
	node = resolve->tokens;
	resolve->tokens = resolve->tokens->next;
	ft_memcpy(&resolve->token, node->data, sizeof(t_token));
	ft_lstdelone(&node, NULL);
}
