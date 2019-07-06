/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_inhibitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 17:28:40 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/02 19:37:27 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		loop_par(t_lexer *lexer)
{
	add_to_buffer(lexer);
	while (get_input(lexer, CUR_CHAR) != ')')
	{
		if (get_input(lexer, CUR_CHAR) == '\\')
			add_to_buffer(lexer);
		else if (get_input(lexer, CUR_CHAR) == '(')
			loop_par(lexer);
		else if (get_input(lexer, CUR_CHAR) == '\"')
			loop_dbquote(lexer);
		else if (get_input(lexer, CUR_CHAR) == '\'')
			loop_quote(lexer);
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

void		loop_maths(t_lexer *lexer)
{
	uint8_t	par;

	add_to_buffer(lexer);
	add_to_buffer(lexer);
	par = 0;
	while (par != 2)
	{
		loop_par(lexer);
		par++;
	}
}

void		loop_braceparam(t_lexer *lexer)
{
	add_to_buffer(lexer);
	add_to_buffer(lexer);
	while (get_input(lexer, CUR_CHAR) != '}')
	{
		if (get_input(lexer, CUR_CHAR) == '\\')
			add_to_buffer(lexer);
		else if (get_input(lexer, CUR_CHAR) == '\"')
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
