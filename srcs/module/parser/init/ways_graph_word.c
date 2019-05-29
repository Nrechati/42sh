/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways_graph_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:42:24 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:41:26 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

void		set_word_token(t_graph *tab_tokens)
{
	static enum e_type tab_good_type[] = {WORD, ALL_REDIRECT, E_ASSIGN,
										E_IO_NUMBER, E_PIPE, END_CMD, E_ERROR};

	tab_tokens[E_STRING].good_type = tab_good_type;
	tab_tokens[E_SPSTRING].good_type = tab_good_type;
	tab_tokens[E_DB_QUOTE].good_type = tab_good_type;
}
