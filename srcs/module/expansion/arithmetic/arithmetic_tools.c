/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 22:43:18 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/02 17:07:37 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	del_arithmetic(t_arithmetic *arithmetic)
{
	ft_lstdel(&arithmetic->tokens, del_token);
	ft_strdel(&arithmetic->expanded);
	vct_del(&arithmetic->input);
}

void	del_infix(t_infix *infix)
{
	ft_stckdestroy(&infix->calcul, NULL);
}

void	m_get_token(t_arithmetic *arithmetic, t_list **node)
{
	if (node)
		ft_lstdel(node, NULL);
	arithmetic->current = arithmetic->tokens;
	arithmetic->tokens = arithmetic->tokens->next;
	arithmetic->current->next = NULL;
	arithmetic->curr_token = arithmetic->current->data;
}

int8_t	get_expansion_input(t_arithmetic *arithmetic,  char *input, size_t start)
{
	char		*str;

	str = NULL;
	ft_asprintf(&str, "%.*s", arithmetic->end - start - 1, input + start);
	if (str == NULL)
	{
		ft_dprintf(2, "Malloc Error on get_expansion_input\n");
		return (FAILURE);
	}
	if (ft_strchr(str, '.'))
	{
		ft_dprintf(2, "42sh: %s: syntax error\n", arithmetic->input);
		return (FAILURE);
	}
	arithmetic->input = vct_dups(str);
	ft_strdel(&str);
	return (SUCCESS);
}

int8_t	find_expansion_end(t_arithmetic *arithmetic,  char *input, size_t start)
{
	size_t		end;

	end = ft_strcspn(input + start, "$") + start;
	while (end > start)
	{
		if (input[end] == ')' && input[end - 1] == ')')
		{
			arithmetic->end = end;
			return (SUCCESS);
		}
		end--;
	}
	ft_dprintf(2, "No end of expansion token\n");
	return (FAILURE);
}
