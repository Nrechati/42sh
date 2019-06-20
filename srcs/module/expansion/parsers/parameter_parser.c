/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 08:31:52 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/20 10:59:44 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int	parameter_check(t_pex_token *token)
{
	if (token->data == NULL)
	{
		ft_dprintf(2, "42sh: bad substitution\n");
		return (-1);
	}
	if (ft_isdigit(token->data[0]))
		return (-1);
	return (0);
}

static int	delimiter_check(t_pex_token *token)
{
	int		len;
	int		index;

	index = 0;
	len = ft_strlen(token->data);
	if (ft_strchr(PEX_FIRST_DELIM, token->data[index]) == NULL)
		return (-1);
	index++;
	while (index < len)
	{
		if (ft_strchr(PEX_NEXT_DELIM, token->data[index]) == NULL)
			return (-1);
	}
	return (0);
}

static int	word_check(t_list *intern, t_pex_token *token)
{
	char	*expanded;

	if ((expanded = expansion_pipeline(intern, token->data)) == NULL)
		return (-1);
	ft_strdel(&token->data);
	token->data = expanded;
	return (0);
}

int			parameter_parse(t_list *intern, t_parameter *parameter)
{
	t_list		*tokens;
	int			result;

	tokens = parameter->tokens;
	if (!tokens)
		return (-1);
	if ((result = parameter_check(tokens->data)) == -1)
		return (result);
	if (tokens->next == NULL)
		return (0);
	if ((result = delimiter_check(tokens->next->data)) == -1)
		return (result);
	if (tokens->next->next == NULL)
		return (0);
	if ((result = word_check(intern, tokens->next->next->data)) == -1)
		return (result);
	return (0);
}

int			parameter_get(t_list *intern, t_parameter *parameter)
{
	t_pex_token	*token;
	char		*data;

	if (ft_lstlen(parameter->tokens) == 1)
	{
		token = parameter->tokens->data;
		if ((data = get_var(intern, token->data)) == NULL)
			parameter->expanded = "";
		else
			parameter->expanded = ft_strdup(data);
		return (0);
	}
	return (-1);
}
