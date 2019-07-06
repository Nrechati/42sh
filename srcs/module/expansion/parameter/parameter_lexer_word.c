/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_lexer_word.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 08:20:37 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/06 10:38:34 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void	pex_next_quote(t_parameter *param)
{
	vct_add(param->buffer, param->source[param->index]);
	param->index++;
	if (param->source[param->index - 1] == '\\')
		return ;
	while (param->source[param->index] != '\'')
	{
		if (param->source[param->index] == '\0')
			return;
		vct_add(param->buffer, param->source[param->index]);
		param->index++;
	}
	vct_add(param->buffer, param->source[param->index]);
	param->index++;
}

static void	pex_next_double_quote(t_parameter *param)
{
	vct_add(param->buffer, param->source[param->index]);
	param->index++;
	if (param->source[param->index - 1] == '\\')
		return ;
	while (param->source[param->index] != '\"')
	{
		if (param->source[param->index] == '\0')
			return;
		vct_add(param->buffer, param->source[param->index]);
		param->index++;
	}
	vct_add(param->buffer, param->source[param->index]);
	param->index++;
}

static void	pex_next_brace(t_parameter *param)
{
	vct_add(param->buffer, param->source[param->index]);
	param->index++;
	if (param->source[param->index - 1] == '\\')
		return ;
	vct_add(param->buffer, param->source[param->index]);
	param->index++;
	while (param->source[param->index] != '}')
	{
		if (param->source[param->index] == '\0')
			return;
		vct_add(param->buffer, param->source[param->index]);
		param->index++;
	}
	vct_add(param->buffer, param->source[param->index]);
	param->index++;
}

void		pex_word(t_parameter *param)
{
	if (param->source[param->index] == '}')
	{
		generate_pex_token(param);
		param->state = PEX_END;
	}
	else if (param->source[param->index] == '\\')
	{
		vct_add(param->buffer, param->source[param->index]);
		param->index++;
		vct_add(param->buffer, param->source[param->index]);
		param->index++;
	}
	else if (ft_strnequ(&param->source[param->index], "${", 2))
		pex_next_brace(param);
	else if (param->source[param->index] == '\"')
		pex_next_double_quote(param);
	else if (param->source[param->index] == '\'')
		pex_next_quote(param);
	else
	{
		vct_add(param->buffer, param->source[param->index]);
		param->index++;
	}
}
