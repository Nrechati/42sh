/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:33:24 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/11 18:34:03 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HISTORY_H
# define FT_HISTORY_H

/*
*****************
**** HISTORY ****
*****************
*/

char		*history(t_registry *shell, char *name, uint64_t option);
void		add_new_entry(t_history *history, char *new);
void		delete_entry(t_history *history, int id);
char		*get_entry(t_history *history, char *search, uint64_t option);
void		print_history(t_history *history, char *elem, uint64_t option);

/*
*****************
***** ENTRY *****
*****************
*/

void	add_entry(t_entry **head, t_entry *new_entry);
t_entry	*create_entry(char *cmd);
void	free_history(t_entry *entry);
void	pop_entry(t_entry **entry, t_entry **head);

#endif
