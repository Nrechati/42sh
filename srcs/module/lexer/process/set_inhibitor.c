/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_inhibitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 17:28:40 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/02 13:52:09 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void	set_doublequoteflag(t_lexer *lexer)
{
	if (get_input(lexer, CUR_CHAR) == '\"')
		lexer->inhibitor &= ~DOUBLEQUOTE_FLAG;
	else if (get_input(lexer, CUR_CHAR) == '$'
			&& get_input(lexer, NEXT_CHAR) == '{')
	{
		lexer->inhibitor |= BRACEPARAM_FLAG;
		set_inhibitor(lexer);
	}
	else if (get_input(lexer, CUR_CHAR) == '$'
			&& get_input(lexer, NEXT_CHAR) == '('
			&& get_input(lexer, NEXT_NEXT_CHAR) == '(')
		lexer->inhibitor |= MATHS_FLAG;
}

static void	set_mathsflag(t_lexer *lexer)
{
	if (get_input(lexer, CUR_CHAR) == ')')
		lexer->parenthesis--;
	else if (get_input(lexer, CUR_CHAR) == '(')
		lexer->parenthesis++;
	else if (get_input(lexer, CUR_CHAR) == '\'')
		lexer->inhibitor |= SINGLEQUOTE_FLAG;
	else if (get_input(lexer, CUR_CHAR) == '\"')
		lexer->inhibitor |= DOUBLEQUOTE_FLAG;
	else if (get_input(lexer, CUR_CHAR) == '$'
			&& get_input(lexer, NEXT_CHAR) == '{')
		lexer->inhibitor |= BRACEPARAM_FLAG;
	else if (get_input(lexer, CUR_CHAR) == '$'
			&& get_input(lexer, NEXT_CHAR) == '('
			&& get_input(lexer, NEXT_NEXT_CHAR) == '(')
		lexer->inhibitor |= MATHS_FLAG;
	if (lexer->parenthesis == 0)
	{
		add_to_buffer(lexer);
		lexer->inhibitor &= ~MATHS_FLAG;
		set_inhibitor(lexer);
	}
}

static void	set_braceparamflag(t_lexer *lexer)
{
	if (get_input(lexer, CUR_CHAR) == '}')
		lexer->parenthesis--;
	else if (get_input(lexer, CUR_CHAR) == '\'')
		lexer->inhibitor |= SINGLEQUOTE_FLAG;
	else if (get_input(lexer, CUR_CHAR) == '\"')
		lexer->inhibitor |= DOUBLEQUOTE_FLAG;
	else if (get_input(lexer, CUR_CHAR) == '$'
			&& get_input(lexer, NEXT_CHAR) == '{')
		lexer->parenthesis++;
	else if (get_input(lexer, CUR_CHAR) == '$'
			&& get_input(lexer, NEXT_CHAR) == '('
			&& get_input(lexer, NEXT_NEXT_CHAR) == '(')
		lexer->inhibitor |= MATHS_FLAG;
	if (lexer->parenthesis == 0)
	{
		add_to_buffer(lexer);
		lexer->inhibitor &= ~BRACEPARAM_FLAG;
		set_inhibitor(lexer);
	}
}

static void	set_noflag(t_lexer *lexer)
{
	if (get_input(lexer, CUR_CHAR) == '\'')
		lexer->inhibitor |= SINGLEQUOTE_FLAG;
	else if (get_input(lexer, CUR_CHAR) == '\"')
		lexer->inhibitor |= DOUBLEQUOTE_FLAG;
	else if (get_input(lexer, CUR_CHAR) == '$'
			&& get_input(lexer, NEXT_CHAR) == '{')
	{
		lexer->inhibitor |= BRACEPARAM_FLAG;
		set_inhibitor(lexer);
	}
	else if (get_input(lexer, CUR_CHAR) == '$'
			&& get_input(lexer, NEXT_CHAR) == '('
			&& get_input(lexer, NEXT_NEXT_CHAR) == '(')
		lexer->inhibitor |= MATHS_FLAG;
}

void		set_inhibitor(t_lexer *lexer)
{
	if (lexer->inhibitor & BACKSLASH_FLAG)
		lexer->inhibitor &= ~BACKSLASH_FLAG;
	if (get_input(lexer, CUR_CHAR) == '\\')
	{
		add_to_buffer(lexer);
		lexer->inhibitor |= BACKSLASH_FLAG;
	}
	else if (lexer->inhibitor == NO_FLAG)
		set_noflag(lexer);
	else if (lexer->inhibitor & BRACEPARAM_FLAG)
		set_braceparamflag(lexer);
	else if (lexer->inhibitor & MATHS_FLAG)
		set_mathsflag(lexer);
	else if (lexer->inhibitor & DOUBLEQUOTE_FLAG)
		set_doublequoteflag(lexer);
	else if (lexer->inhibitor & SINGLEQUOTE_FLAG)
	{
		if (get_input(lexer, CUR_CHAR) == '\'')
			lexer->inhibitor &= ~SINGLEQUOTE_FLAG;
	}
}
