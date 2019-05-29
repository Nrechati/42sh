/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_analyzer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 22:13:42 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:52:29 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"


static void	bzero_parsing(t_pstate parsing)
{
	int		index;
	int		state;

	index = 0;
	while (index < PARSE_STATES)
	{
		state = 0;
		while (state < NB_OF_TOKENS)
			parsing[index][state++] = error_parser;
		++index;
	}
}

static void	init_io_rediction_parser(t_pstate parsing)
{
	init_io(parsing);
	init_io_redirect(parsing);
	init_io_filename(parsing);
	init_io_filename_and(parsing);
	init_io_flush(parsing);
	init_io_flush_and(parsing);
	init_io_dup_move(parsing);
	init_heredoc(parsing);
	init_heredoc_redirect(parsing);
	init_heredoc_delimiter(parsing);
	init_io_heredoc(parsing);
	init_io_heredoc_redirect(parsing);
	init_dup_move(parsing);
	init_pipe(parsing);
	init_io_heredoc_delimiter(parsing);
	init_flush_redirect(parsing);
}

t_pstate	*init_parsing(void)
{
	static t_pstate parsing;

	bzero_parsing(parsing);
	init_start(parsing);
	init_string(parsing);
	init_special_string(parsing);
	init_flush_string(parsing);
	init_separator(parsing);
	init_redirect(parsing);
	init_filename(parsing);
	init_io_rediction_parser(parsing);
	return (&parsing);
}
