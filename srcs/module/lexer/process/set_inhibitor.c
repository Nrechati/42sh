/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_inhibitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 17:28:40 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/02 16:48:50 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		loop_maths(t_lexer *lexer)
{
	//// PARENTHESIS
	add_to_buffer(lexer);
	add_to_buffer(lexer);
	add_to_buffer(lexer);
	while (get_input(lexer, CUR_CHAR) != ')')
	{
		if (get_input(lexer, CUR_CHAR) == '\"')
			loop_dbquote(lexer);
		else if (get_input(lexer, CUR_CHAR) == '$'
				&& get_input(lexer, NEXT_CHAR) == '{')
			loop_braceparam(lexer);
		else if (get_input(lexer, CUR_CHAR) == '$'
			&& get_input(lexer, NEXT_CHAR) == '('
			&& get_input(lexer, NEXT_NEXT_CHAR) == '(')
			loop_maths(lexer);
		add_to_buffer(lexer);
	}
}

void		loop_braceparam(t_lexer *lexer)
{
	add_to_buffer(lexer);
	add_to_buffer(lexer);
	while (get_input(lexer, CUR_CHAR) != '}')
	{
		if (get_input(lexer, CUR_CHAR) == '\"')
			loop_dbquote(lexer);
		else if (get_input(lexer, CUR_CHAR) == '$'
				&& get_input(lexer, NEXT_CHAR) == '{')
			loop_braceparam(lexer);
		else if (get_input(lexer, CUR_CHAR) == '$'
			&& get_input(lexer, NEXT_CHAR) == '('
			&& get_input(lexer, NEXT_NEXT_CHAR) == '(')
			loop_maths(lexer);
		add_to_buffer(lexer);
	}
}

void		loop_dbquote(t_lexer *lexer)
{
	add_to_buffer(lexer);
	while (get_input(lexer, CUR_CHAR) != '\"')
	{
		if (get_input(lexer, CUR_CHAR) == '\\')
			add_to_buffer(lexer);
		else if (get_input(lexer, CUR_CHAR) == '$'
				&& get_input(lexer, NEXT_CHAR) == '{')
			loop_braceparam(lexer);
		else if (get_input(lexer, CUR_CHAR) == '$'
			&& get_input(lexer, NEXT_CHAR) == '('
			&& get_input(lexer, NEXT_NEXT_CHAR) == '(')
			loop_maths(lexer);
		add_to_buffer(lexer);
	}
}

void		loop_quote(t_lexer *lexer)
{
	add_to_buffer(lexer);
	while (get_input(lexer, CUR_CHAR) != '\'')
		add_to_buffer(lexer);
}

uint8_t		is_inhib(t_lexer *lexer)
{
	if (get_input(lexer, CUR_CHAR) == '\\')
		add_to_buffer(lexer);
	else if (get_input(lexer, CUR_CHAR) == '\'')
		loop_quote(lexer);
	else if (get_input(lexer, CUR_CHAR) == '\"')
		loop_dbquote(lexer);
	else if (get_input(lexer, CUR_CHAR) == '$'
			&& get_input(lexer, NEXT_CHAR) == '{')
		loop_braceparam(lexer);
	else if (get_input(lexer, CUR_CHAR) == '$'
		&& get_input(lexer, NEXT_CHAR) == '('
		&& get_input(lexer, NEXT_NEXT_CHAR) == '(')
		loop_maths(lexer);
	else
		return (FALSE);
	return (TRUE);
}

void		set_inhibitor(t_lexer *lexer)
{
	if (is_inhib(lexer) == TRUE)
		add_to_buffer(lexer);
}
