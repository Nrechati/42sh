/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_maths_interface.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:59:11 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/27 18:58:25 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static t_token	generate_token_m(t_lexer *lexer)
{
	t_token	token;

	token.type = lexer->token_mtype;
	token.data = NULL;
	if (token.type == E_M_STRING
		|| token.type == E_M_NB_DEC
		|| token.type == E_M_NB_OCT
		|| token.type == E_M_NB_HEX)
		token.data = ft_strdup(vct_get_string(lexer->buffer));
	return (token);
}

void			out_lexer_m(t_lexer *lexer)
{
	t_token	token;
	t_list	*node;

	token = generate_token_m(lexer);
	if ((node = ft_lstnew(&token, sizeof(token))) == NULL)
	{
		ft_strdel(&token.data);
		return ;
	}
	ft_lstaddback(&lexer->tokens, node);
	lexer->state = lexer->token_mtype == E_M_END ? L_FINISH : L_PROCESS;
	lexer->last_token_mtype = lexer->token_mtype;
	lexer->token_mtype = E_M_DEFAULT;
	vct_reset(lexer->buffer);
}

uint8_t	is_operator_m(t_lexer *lexer)
{
	size_t	len_op;
	size_t	i;
	int		type;
	char	*current;

	i = 0;
	type = 16;
	current = lexer->input->buffer + lexer->index;
	while (type >= 0)
	{
		len_op = ft_strlen(g_shell->grammar_m[type]);
		if (ft_strnequ(g_shell->grammar_m[type], current, len_op) == TRUE)
		{
			if (lexer->token_mtype != E_M_DEFAULT
					&& lexer->last_token_mtype != E_M_DELIMITER)
				out_lexer_m(lexer);
			while (i++ < len_op)
				add_to_buffer(lexer);
			lexer->token_mtype = type;
			return (TRUE);
		}
		type--;
	}
	return (FALSE);
}

uint8_t	is_input_end_m(t_lexer *lexer)
{
	if (get_input(lexer, CUR_CHAR) == '\0')
	{
		if (lexer->token_mtype != E_M_DEFAULT
				&& lexer->last_token_mtype != E_M_DELIMITER)
			out_lexer_m(lexer);
		lexer->token_mtype = E_M_END;
		return (TRUE);
	}
	return (FALSE);
}

uint8_t	is_number_m(t_lexer *lexer)
{
	if (lexer->token_mtype == E_M_DEFAULT)
	{
		if (ft_isdigit(get_input(lexer, CUR_CHAR)) == TRUE)
		{
			if (get_input(lexer, CUR_CHAR) == '0')
			{
				if (get_input(lexer, NEXT_CHAR) == 'x'
						|| get_input(lexer, NEXT_CHAR) == 'X')
				{
					add_to_buffer(lexer);
					lexer->token_mtype = E_M_NB_HEX;
				}
				else
					lexer->token_mtype = E_M_NB_OCT;
			}
			else
				lexer->token_mtype = E_M_NB_DEC;
			return (TRUE);
		}
	}
	else if (lexer->token_mtype == E_M_NB_DEC
		|| lexer->token_mtype == E_M_NB_OCT
		|| lexer->token_mtype == E_M_NB_HEX)
		return (TRUE);
	return (FALSE);
}

uint8_t	is_delimiter_m(t_lexer *lexer)
{
	uint8_t	ret;

	ret = FALSE;
	if (get_input(lexer, CUR_CHAR) == ' ')
		ret = TRUE;
	else if (get_input(lexer, CUR_CHAR) == '\t')
		ret = TRUE;
	else if (get_input(lexer, CUR_CHAR) == '\n')
		ret = TRUE;
	if (ret == TRUE)
	{
		if (lexer->token_mtype != E_M_DEFAULT)
			out_lexer_m(lexer);
	}
	return (ret);
}

void			process_maths_lexer(t_lexer *lexer)
{
	if (is_input_end_m(lexer) == TRUE)
		lexer->state = L_OUT;
	else if (is_delimiter_m(lexer) == TRUE)
	{
		if (lexer->last_token_mtype != E_M_DELIMITER)
			lexer->state = L_OUT;
	}
	else if (is_operator_m(lexer) == TRUE)
		lexer->state = L_OUT;
	else if (is_number_m(lexer) == TRUE)
		add_to_buffer(lexer);
	else
	{
		add_to_buffer(lexer);
		lexer->token_mtype = E_M_STRING;
	}
}
