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

# define INIT_HISTORY		0x0001
# define FREE_HISTORY		0x0002
# define WRITE_HISTFILE		0x0004
# define PRINT_HISTORY		0x0008
# define ADD_ENTRY			0x0010
# define POP_ENTRY			0x0020
# define GET_ENTRY			0x0040
# define BY_ID				0x0100
# define BY_NAME			0x0200
# define REL				0x1000
# define PREV				0x2000
# define NEXT				0x4000
# define RESET_HEAD			0x8000

typedef	struct	s_entry	t_entry;

struct			s_entry
{
	t_entry		*next;
	t_entry		*prev;
	char		*cmd;
};

typedef struct	s_history
{
	t_entry		*entry;
	t_entry		*head_ptr;
	int			nb_of_entries;
	int			first_search;
}				t_history;

/*
*****************
**** HISTORY ****
*****************
*/

char		*history(t_registry *shell, char *name, uint64_t option);
void		add_new_entry(t_history *history, char *new);
void		delete_entry(t_history *history, int id);
char		*get_entry(t_history *history, char *search, uint64_t option);

/*
*****************
***** ENTRY *****
*****************
*/

void	add_entry(t_entry **head, t_entry *new_entry);
t_entry	*create_entry(char *cmd);
void	free_history(t_entry *entry);
void	pop_entry(t_entry **entry);

#endif
