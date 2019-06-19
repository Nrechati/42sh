/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 20:19:38 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/17 14:22:49 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char				*assign_token_data(t_lexer *machine, t_token *token)
{
	enum e_type		i;

	i = 0;
	while (i < TOKEN_WITH_DATA)
	{
		if (token->type == machine->lexinfo->duplicate[i++]
			&& get_buffer(machine, CUR_CHAR) != '\0')
		{
			if (machine->data != NULL)
				ft_asprintf(&token->data, "%s%s", machine->data
						, machine->buffer->buffer);
			else
				token->data = ft_strdup(machine->buffer->buffer);
			ft_strdel(&machine->data);
		}
	}
	return (token->data);
}

static enum e_type	check_last_lexer(t_lexer *machine)
{
	enum e_type		i;

	i = 0;
	while (i < TOKEN_WITH_DATA)
	{
		if (machine->last_lexer == machine->lexinfo->duplicate[i])
			return (machine->lexinfo->duplicate[i]);
		++i;
	}
	i = 0;
	while (i < SPECIAL_SIGNS)
	{
		if (machine->last_lexer == machine->lexinfo->special_signs[i])
			return (machine->lexinfo->special_signs[i]);
		++i;
	}
	if (machine->last_lexer == E_IO_NUMBER)
		return (E_IO_NUMBER);
	if (machine->last_lexer == E_NEWLINE)
		return (E_NEWLINE);
	return (machine->last_lexer == E_END ? E_END : E_ERROR);
}

static enum e_type	check_char(t_lexer *machine)
{
	enum e_type		i;
	char			*s;

	i = 0;
	s = ALLCHAR;
	while (i < SINGLE_SIGNS)
	{
		if (get_buffer(machine, CUR_CHAR) == s[i])
			return (i);
		++i;
	}
	return (E_ERROR);
}

static enum e_type	define_type(t_lexer *machine)
{
	enum e_type		result;

	if ((result = check_last_lexer(machine)) != E_ERROR)
		return (result);
	else if ((result = check_char(machine)) != E_ERROR)
		return (result);
	return (E_STRING);
}

t_token				generate_token(t_lexer *machine)
{
	t_token			token;

	token.type = define_type(machine);
	token.data = NULL;
	assign_token_data(machine, &token);
	if (machine->last_lexer != E_END)
	{
		vct_reset(machine->buffer);
		machine->last_lexer = E_DEFAULT;
	}
	if (machine->io_detect)
		--machine->io_detect;
	return (token);
}
