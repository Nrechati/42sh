/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:41:49 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/15 11:41:55 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static uint8_t	manage_error_and_subprompt(const char **grammar,
					enum e_type state, enum e_type type, t_list **lst)
{
	if (need_subprompt(state, type) == TRUE)
	{
		parser_subprompt(lst);
		return (TRUE);
	}
	ft_dprintf(2, "42sh: syntax error near unexpected token `%s'\n",
				grammar[type]);
	return (FALSE);
}

static uint8_t	state_is_ok(enum e_type to_find, enum e_type *current,
							enum e_type possible_state[])
{
	uint8_t		i;

	i = 0;
	if (possible_state == NULL)
		return (FALSE);
	while (possible_state[i] != E_ERROR)
	{
		if (to_find == possible_state[i])
		{
			*current = to_find;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int8_t			process_parser(t_parser *parser, t_list *lst)
{
	t_token		*token;
	t_list		*tmp;
	enum e_type	state;

	state = E_START;
	tmp = lst;
	while (lst != NULL)
	{
		token = (t_token *)lst->data;
		if ((state_is_ok(token->type, &state,
						parser->graph[state].good_type)) == FALSE)
		{
			if (manage_error_and_subprompt(parser->grammar,
						state, token->type, &tmp) == FALSE)
				return (FAILURE);
			lst = tmp;
		}
		else
			tmp = lst;
		lst = lst->next;
	}
	return (SUCCESS);
}

int8_t			parser(t_list *lst)
{
	static t_parser	*parser = NULL;

	if (parser == NULL)
		parser = init_parser();
	return (process_parser(parser, lst));
}
