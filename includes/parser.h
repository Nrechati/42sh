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

int8_t		parser(t_list *lst);
uint8_t		need_subprompt(enum e_type state, enum e_type type);
void		parser_subprompt(t_list **lst);

/*
*************** INIT
*/

t_graph		*generate_graph(void);
void		set_start_token(t_graph *tab_tokens);
void		set_word_token(t_graph *tab_tokens);
void		set_redirect_token(t_graph *tab_tokens);
void		set_assign_token(t_graph *tab_tokens);
void		set_pipe_token(t_graph *tab_tokens);
void		set_ionumber_token(t_graph *tab_tokens);

#endif
