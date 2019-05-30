/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 13:39:31 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:55:15 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "struct.h"

/*
*****************************************************
****************** GRAMMAR PARSER  ******************
*****************************************************
*/

int8_t		parser(t_list *lst);
t_graph		*generate_graph(void);
void		set_start_token(t_graph *tab_tokens);
void		set_word_token(t_graph *tab_tokens);
void		set_redirect_token(t_graph *tab_tokens);
void		set_assign_token(t_graph *tab_tokens);
void		set_pipe_token(t_graph *tab_tokens);
void		set_ionumber_token(t_graph *tab_tokens);

/*
*************** GRAMMAR PARSER DEBUG
*/

void		print_token_debug(t_token *token);
void		print_arrow_debug(int which);
void		print_error_debug(enum e_type type, int which);
void		print_result_debug(int which);

/*
*****************************************************
**************** APPLICATION PARSER *****************
*****************************************************
*/

t_list		*analyzer(t_resolution *resolve);
void		reset_analyzer(t_registry *shell, t_resolution *resolve);
t_analyzer	*init_analyzer(void);
void		init_process(t_process *process);
void		start_analyzer(t_resolution *resolve);
void		separator_analyzer(t_resolution *resolve);
void		stop_analyzer(t_resolution *resolve);
void		end_analyzer(t_resolution *resolve);
void		error_analyzer(t_resolution *resolve);

void		string_analyzer(t_resolution *resolve);
void		special_string_analyzer(t_resolution *resolve);
void		flush_string(t_resolution *resolve);

void		redirect_analyzer(t_resolution *resolve);
void		redirect_and_analyzer(t_resolution *resolve);
void		pipe_analyzer(t_resolution *resolve);
void		filename_analyzer(t_resolution *resolve);
void		dup_move_analyzer(t_resolution *resolve);
void		flush_redirect(t_resolution *resolve);
void		flush_redirect_and(t_resolution *resolve);

void		io_analyzer(t_resolution *resolve);
void		io_redirect_analyzer(t_resolution *resolve);
void		io_redirect_and_analyzer(t_resolution *resolve);
void		io_dup_move_analyzer(t_resolution *resolve);
void		io_filename_analyzer(t_resolution *resolve);
void		io_and_redirect_flush(t_resolution *resolve);
void		io_redirect_flush(t_resolution *resolve);

void		heredoc_analyzer(t_resolution *resolve);
void		io_heredoc_analyzer(t_resolution *resolve);
void		heredoc_delimiter(t_resolution *resolve);

void		delete_process(void *data);
char		*expand_string(t_list *lst, char *str);
char		*string_expansion(t_resolution *resolve, char *str);
char		*tilde(t_resolution *resolve, char *str);
char		*variable_expansion(t_resolution *resolve, char *str);
void		quote_removal(char *str);
char		character_swap(char swapped);
t_quote		select_quoting(t_quote quote, char c);
int			is_ionumber(t_resolution *resolve, char *str);
void		check_filename(t_resolution *resolve);
t_type		pop_token_type(t_stack *stack);
char		*pop_token_data(t_stack *stack);
void		get_token(t_resolution *resolve);
void		generate_filedesc(t_resolution *resolve, int first, int second
					, int action);
#endif
