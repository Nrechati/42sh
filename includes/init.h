/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 22:18:11 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:55:15 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "parser.h"

void	init_io(t_analyzer analyzer);
void	init_io_filename(t_analyzer analyzer);
void	init_io_filename_and(t_analyzer analyzer);
void	init_io_flush(t_analyzer analyzer);
void	init_io_flush_and(t_analyzer analyzer);
void	init_io_redirect(t_analyzer analyzer);
void	init_pipe(t_analyzer analyzer);
void	init_io_dup_move(t_analyzer analyzer);
void	init_io_redirect(t_analyzer analyzer);
void	init_io_move(t_analyzer analyzer);
void	init_io_dup(t_analyzer analyzer);
void	init_io_heredoc_redirect(t_analyzer analyzer);
void	init_io_heredoc_delimiter(t_analyzer analyzer);
void	init_io_heredoc(t_analyzer analyzer);
void	init_string(t_analyzer analyzer);
void	init_special_string(t_analyzer analyzer);
void	init_flush_string(t_analyzer analyzer);
void	init_filename(t_analyzer analyzer);
void	init_start(t_analyzer analyzer);
void	init_separator(t_analyzer analyzer);
void	init_redirect(t_analyzer analyzer);
void	init_dup_move(t_analyzer analyzer);
void	init_flush_redirect(t_analyzer analyzer);
void	init_pipe(t_analyzer analyzer);
void	init_heredoc(t_analyzer analyzer);
void	init_heredoc_redirect(t_analyzer analyzer);
void	init_heredoc_delimiter(t_analyzer analyzer);

#endif
