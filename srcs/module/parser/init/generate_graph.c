/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_graph.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:42:01 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:52:29 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_graph		*generate_graph(void)
{
	static t_graph	graph[NB_OF_TOKENS];

	ft_bzero(&graph, sizeof(graph));
	set_start_token(graph);
	set_word_token(graph);
	set_redirect_token(graph);
	set_assign_token(graph);
	set_pipe_token(graph);
	set_ionumber_token(graph);
	return (graph);
}
