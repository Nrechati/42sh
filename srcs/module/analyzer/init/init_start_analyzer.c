/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_start_analyzer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 22:05:16 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:52:29 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	init_start(t_analyzer analyzer)
{
	analyzer[P_START][E_STRING] = string_analyzer;
	analyzer[P_START][E_SPSTRING] = special_string_analyzer;
	analyzer[P_START][E_GREAT] = redirect_analyzer;
	analyzer[P_START][E_GREATAND] = redirect_and_analyzer;
	analyzer[P_START][E_LESS] = redirect_analyzer;
	analyzer[P_START][E_LESSAND] = redirect_and_analyzer;
	analyzer[P_START][E_DGREAT] = redirect_analyzer;
	analyzer[P_START][E_DLESS] = redirect_analyzer;
	analyzer[P_START][E_DLESSDASH] = redirect_analyzer;
	analyzer[P_START][E_ANDGREAT] = redirect_analyzer;
	analyzer[P_START][E_ANDDGREAT] = redirect_analyzer;
	analyzer[P_START][E_IO_NUMBER] = io_analyzer;
	analyzer[P_START][E_SEMICOLON] = separator_analyzer;
	analyzer[P_START][E_NEWLINE] = separator_analyzer;
	analyzer[P_START][E_END] = end_analyzer;
}

void	init_separator(t_analyzer analyzer)
{
	analyzer[P_SEPARATOR][E_STRING] = stop_analyzer;
	analyzer[P_SEPARATOR][E_SPSTRING] = stop_analyzer;
	analyzer[P_SEPARATOR][E_GREAT] = stop_analyzer;
	analyzer[P_SEPARATOR][E_GREATAND] = stop_analyzer;
	analyzer[P_SEPARATOR][E_LESS] = stop_analyzer;
	analyzer[P_SEPARATOR][E_LESSAND] = stop_analyzer;
	analyzer[P_SEPARATOR][E_DGREAT] = stop_analyzer;
	analyzer[P_SEPARATOR][E_DLESS] = stop_analyzer;
	analyzer[P_SEPARATOR][E_DLESSDASH] = stop_analyzer;
	analyzer[P_SEPARATOR][E_ANDDGREAT] = stop_analyzer;
	analyzer[P_SEPARATOR][E_SEMICOLON] = stop_analyzer;
	analyzer[P_SEPARATOR][E_NEWLINE] = stop_analyzer;
	analyzer[P_SEPARATOR][E_END] = end_analyzer;
}

void	init_redirect(t_analyzer analyzer)
{
	analyzer[P_REDIRECT][E_STRING] = filename_analyzer;
	analyzer[P_REDIRECT][E_SPSTRING] = filename_analyzer;
	analyzer[P_REDIRECT_AND][E_SPSTRING] = dup_move_analyzer;
	analyzer[P_REDIRECT_AND][E_STRING] = dup_move_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_STRING] = string_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_SPSTRING] = special_string_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_GREAT] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_GREATAND] = redirect_and_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_LESS] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_DLESS] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_LESSAND] = redirect_and_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_DGREAT] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_DLESSDASH] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_ANDDGREAT] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_IO_NUMBER] = io_analyzer;
	analyzer[P_REDIRECT_FLUSH_AND][E_PIPE] = flush_string;
	analyzer[P_REDIRECT_FLUSH_AND][E_SEMICOLON] = flush_string;
	analyzer[P_REDIRECT_FLUSH_AND][E_NEWLINE] = flush_string;
	analyzer[P_REDIRECT_FLUSH_AND][E_END] = flush_string;
}

void	init_flush_redirect(t_analyzer analyzer)
{
	analyzer[P_REDIRECT_FLUSH][E_STRING] = string_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_SPSTRING] = special_string_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_GREAT] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_GREATAND] = redirect_and_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_LESS] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_DLESS] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_LESSAND] = redirect_and_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_DGREAT] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_DLESSDASH] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_ANDDGREAT] = redirect_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_IO_NUMBER] = io_analyzer;
	analyzer[P_REDIRECT_FLUSH][E_PIPE] = flush_string;
	analyzer[P_REDIRECT_FLUSH][E_SEMICOLON] = flush_string;
	analyzer[P_REDIRECT_FLUSH][E_NEWLINE] = flush_string;
	analyzer[P_REDIRECT_FLUSH][E_END] = flush_string;
}

void	init_dup_move(t_analyzer analyzer)
{
	analyzer[P_DUP_MOVE][E_STRING] = flush_redirect_and;
	analyzer[P_DUP_MOVE][E_SPSTRING] = flush_redirect_and;
	analyzer[P_DUP_MOVE][E_GREAT] = flush_redirect_and;
	analyzer[P_DUP_MOVE][E_GREATAND] = flush_redirect_and;
	analyzer[P_DUP_MOVE][E_LESS] = flush_redirect_and;
	analyzer[P_DUP_MOVE][E_LESSAND] = flush_redirect_and;
	analyzer[P_DUP_MOVE][E_DGREAT] = flush_redirect_and;
	analyzer[P_DUP_MOVE][E_ANDDGREAT] = flush_redirect_and;
	analyzer[P_DUP_MOVE][E_IO_NUMBER] = flush_redirect_and;
	analyzer[P_DUP_MOVE][E_PIPE] = flush_redirect_and;
	analyzer[P_DUP_MOVE][E_SEMICOLON] = flush_redirect_and;
	analyzer[P_DUP_MOVE][E_NEWLINE] = flush_redirect_and;
	analyzer[P_DUP_MOVE][E_END] = flush_redirect_and;
}
