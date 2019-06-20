/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 08:16:54 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/20 10:47:08 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void	pex_parameter(t_parameter *param)
{
	if (ft_strchr(PEX_PARAM_INTERUPT, param->source[param->index]))
	{
		generate_pex_token(param);
		if (param->source[param->index] == '}')
		{
			param->index++;
			param->state = PEX_END;
		}
		else
			param->state = PEX_DELIM;
	}
	else
	{
		vct_add(param->buffer, param->source[param->index]);
		param->index++;
	}
}

static void	pex_delimiter(t_parameter *param)
{
	if (ft_strchr(PEX_VALID_DELIM, param->source[param->index]) == NULL)
	{
		generate_pex_token(param);
		if (param->source[param->index] == '}')
		{
			param->index++;
			param->state = PEX_END;
		}
		else
			param->state = PEX_WORD;
	}
	else
	{
		vct_add(param->buffer, param->source[param->index]);
		param->index++;
	}
}

static void	init_paramexp(t_paramexp state[PEX_STATES])
{
	state[PEX_PARAM] = pex_parameter;
	state[PEX_DELIM] = pex_delimiter;
	state[PEX_WORD] = pex_word;
	state[PEX_END] = NULL;
}

void	generate_pex_token(t_parameter *param)
{
	t_list			*node;
	t_pex_token		token;
	char			*str;

	ft_bzero(&token, sizeof(t_pex_token));
	token.type = param->state;
	str = vct_get_string(param->buffer);
	if (!str || *str == '\0')
		token.data = NULL;
	else
		token.data = ft_strdup(vct_get_string(param->buffer));
	node = ft_lstnew(&token, sizeof(t_pex_token));
	ft_lstaddback(&param->tokens, node);
	vct_del(&param->buffer);
	param->buffer = vct_new(DEFAULT_PEX_BUFFER);
}

void	parameter_lexer(t_parameter *parameter)
{
	static t_paramexp	state[PEX_STATES];

	if (state[0] == NULL)
		init_paramexp(state);
	while (parameter->state != PEX_END)
		state[parameter->state](parameter);
}