/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_module.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 20:28:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/02 18:45:01 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

uint8_t	token_checker(t_lexer *lexer, int start, int end)
{
	size_t	len_op;
	size_t	i;
	int		type;
	char	*current;

	i = 0;
	type = start + 1;
	current = lexer->input->buffer + lexer->index;
	while (--type >= end)
	{
		len_op = ft_strlen(g_shell->grammar[type]);
		if (ft_strnequ(g_shell->grammar[type], current, len_op) == TRUE)
		{
			if (lexer->token_type != E_DEFAULT)
				out_lexer(lexer);
			while (i++ < len_op)
				add_to_buffer(lexer);
			lexer->token_type = type;
			return (TRUE);
		}
	}
	return (FALSE);
}

static uint8_t	last_is_redirect(t_lexer *lexer)
{
	if (lexer->last_token_type == E_DLESS
		|| lexer->last_token_type == E_DGREAT
		|| lexer->last_token_type == E_LESS
		|| lexer->last_token_type == E_GREAT
		|| lexer->last_token_type == E_LESSAND
		|| lexer->last_token_type == E_GREATAND
		|| lexer->last_token_type == E_ANDGREAT
		|| lexer->last_token_type == E_ANDDGREAT
		|| lexer->last_token_type == E_DLESSDASH)
		return (TRUE);
	return (FALSE);
}

uint8_t	is_io_number(t_lexer *lexer) 
{
	uint8_t	ret;

	ret = FALSE;
	if (last_is_redirect(lexer) == TRUE)
		ret = FALSE;
	else if (lexer->token_type != E_DEFAULT)
		ret = FALSE;
	else if (get_input(lexer, NEXT_CHAR) == ' '
			|| get_input(lexer, NEXT_CHAR) == '\t')
		ret = FALSE;
	else if (ft_isdigit(get_input(lexer, CUR_CHAR)) == FALSE)
		ret = FALSE;
	else if (get_input(lexer, NEXT_CHAR) == '<')
		ret = TRUE;
	else if (get_input(lexer, NEXT_CHAR) == '>')
		ret = TRUE;
	else if (get_input(lexer, NEXT_CHAR) == '&'
			&& get_input(lexer, NEXT_NEXT_CHAR) == '>')
		ret = TRUE;
	if (ret == TRUE)
	{
		add_to_buffer(lexer);
		lexer->token_type = E_IO_NUMBER;
	}
	return (ret);
}

uint8_t	is_delimiter(t_lexer *lexer)
{
	uint8_t	ret;

	ret = FALSE;
	if (get_input(lexer, CUR_CHAR) == ' ')
		ret = TRUE;
	else if (get_input(lexer, CUR_CHAR) == '\t')
		ret = TRUE;
	if (ret == TRUE && lexer->token_type != E_DEFAULT)
		out_lexer(lexer);
	return (ret);
}

uint8_t	is_input_end(t_lexer *lexer)
{
	if (get_input(lexer, CUR_CHAR) == '\0')
	{
		if (lexer->token_type != E_DEFAULT)
			out_lexer(lexer);
		lexer->token_type = E_END;
		return (TRUE);
	}
	return (FALSE);
}

uint8_t	is_assignation(t_lexer *lexer)
{
	if (get_input(lexer, CUR_CHAR) == '='
		&& lexer->token_type == E_STRING
		&& lexer->assignation == POSSIBLE)
	{
		if (is_valid_variable(lexer->buffer->buffer) == FALSE)
			return (FALSE);
		lexer->token_type = E_ASSIGN;
		lexer->index++;
		out_lexer(lexer);
		lexer->assignation = LISTEN;
		lexer->token_type = E_STRING;
		return (TRUE);
	}
	return (FALSE);
}
