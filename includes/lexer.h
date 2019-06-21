/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:35:44 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/20 18:07:24 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

t_list		*lexer(t_vector *line);

/*
*****************************************************
******************** INTERFACE **********************
*****************************************************
*/

void		process_lexer(t_lexer *lexer);
void		out_lexer(t_lexer *lexer);
void		set_inhibitor(t_lexer *lexer);

/*
*****************************************************
********************** TOOLS ************************
*****************************************************
*/

void		add_to_buffer(t_lexer *lexer);
char		get_buffer(t_lexer *lexer, uint8_t pos);
char		get_input(t_lexer *lexer, uint8_t pos);


/*
*****************************************************
******************* TEMP DISPLAY ********************
*****************************************************
*/

void		print_token(void *data);
void		lexer_print_debug(t_registry *shell, t_list *token_list);

#endif
