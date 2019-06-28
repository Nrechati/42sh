/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_assign_analyzer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:59:55 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/27 23:13:30 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	init_assign_flush(t_analyzer analyzer)
{
	analyzer[P_ASSIGN_FLUSH][E_STRING] = string_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_ASSIGN] = assign_name_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_GREAT] = redirect_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_GREATAND] = redirect_and_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_LESS] = redirect_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_LESSAND] = redirect_and_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_DGREAT] = redirect_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_DLESS] = redirect_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_DLESSDASH] = redirect_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_ANDGREAT] = redirect_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_ANDDGREAT] = redirect_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_IO_NUMBER] = io_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_SEMICOLON] = stop_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_AND] = stop_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_NEWLINE] = stop_analyzer;
	analyzer[P_ASSIGN_FLUSH][E_END] = end_analyzer;
}

void	init_assign_data(t_analyzer analyzer)
{
	analyzer[P_ASSIGN_NAME][E_STRING] = assign_data_analyzer;
	analyzer[P_ASSIGN_DATA][E_STRING] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_ASSIGN] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_GREAT] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_GREATAND] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_LESS] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_LESSAND] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_DGREAT] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_DLESS] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_DLESSDASH] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_ANDGREAT] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_ANDDGREAT] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_IO_NUMBER] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_PIPE] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_SEMICOLON] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_NEWLINE] = assign_flush_analyzer;
	analyzer[P_ASSIGN_DATA][E_END] = assign_flush_analyzer;
}
