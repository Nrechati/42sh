/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:28:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/20 18:32:36 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	out_lexer(t_lexer *lexer)
{
	t_list	*node;
	t_token	token;

	token.type = lexer->token_type;
	token.data = NULL;
	if (token.type == E_STRING
		|| token.type == E_ASSIGN
		|| token.type == E_IO_NUMBER)
		token.data = ft_strdup(vct_get_string(lexer->buffer));
	if ((node = ft_lstnew(&token, sizeof(token))) == NULL)
	{
		ft_strdel(&token.data);
		return ;
	}
	ft_lstaddback(&lexer->tokens, node);
	lexer->state = lexer->token_type == E_END ? L_FINISH : L_PROCESS;
	lexer->assignation = lexer->token_type == E_STRING ? IMPOSSIBLE : POSSIBLE;
	lexer->token_type = E_DEFAULT;
	lexer->assignation = FALSE;
	vct_reset(lexer->buffer);
}

uint8_t	token_checker(t_lexer *lexer, int start, int end)
{
	size_t	len_op;
	size_t	i;
	int		type;
	char	*current;

	i = 0;
	type = start;
	current = lexer->input->buffer + lexer->index;
	while (type >= end)
	{
		len_op = ft_strlen(g_grammar[type]);
		if (ft_strnequ(g_grammar[type], current, len_op) == TRUE)
		{
			if (lexer->token_type != E_DEFAULT)
				out_lexer(lexer);
			while (i++ < len_op)
				add_to_buffer(lexer);
			lexer->token_type = type;
			return (TRUE);
		}
		type--;
	}
	return (FALSE);
}

uint8_t	is_operator(t_lexer *lexer) 
{
	return (token_checker(lexer, 29, 1));
}

uint8_t	is_reserved_word(t_lexer *lexer) 
{
	if (lexer->assignation == TRUE)
		return (FALSE);
	return (token_checker(lexer, 42, 30));
}

uint8_t	is_io_number(t_lexer *lexer) 
{
	uint8_t	ret;

	ret = FALSE;
	if (lexer->token_type != E_DEFAULT)
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
	{
		out_lexer(lexer);
	}
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
		&& lexer->assignation != IMPOSSIBLE
		&& lexer->assignation != LISTEN)
	{
		lexer->token_type = E_ASSIGN;
		lexer->index++;
		out_lexer(lexer);
		lexer->assignation = LISTEN;
		lexer->token_type = E_STRING;
		return (TRUE);
	}
	return (FALSE);
}

void	process_lexer(t_lexer *lexer)
{
	set_inhibitor(lexer);
	if (is_input_end(lexer) == TRUE)
		lexer->state = L_OUT;
	else if (lexer->inhibitor != NO_FLAG)
	{
		add_to_buffer(lexer);
		lexer->token_type = E_STRING;
	}
	else if (is_io_number(lexer) == TRUE)
		lexer->state = L_OUT;
	else if (is_delimiter(lexer) == TRUE)
		lexer->index++;
	else if (is_operator(lexer) == TRUE)
		lexer->state = L_OUT;
	else if (is_reserved_word(lexer) == TRUE)
		;
	else if (is_assignation(lexer) == TRUE)
		;
	else
	{
		add_to_buffer(lexer);
		lexer->token_type = E_STRING;
	}
}
