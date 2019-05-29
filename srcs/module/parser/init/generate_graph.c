/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_graph.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:42:01 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:41:26 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h" //TMP
#include "parser.h"

void			generate_graph(t_registry *shell)
{
	generate_grammar(shell);
	set_start_token(shell->graph);
	set_word_token(shell->graph);
	set_redirect_token(shell->graph);
	set_assign_token(shell->graph);
	set_pipe_token(shell->graph);
	set_ionumber_token(shell->graph);
}
