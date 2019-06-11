/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:33:24 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/11 18:34:03 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HISTORIC_H
# define FT_HISTORIC_H

# define LIST_OK	0
# define LIST_EMPTY 1

typedef	struct s_circle_list	t_circle_list;

struct							s_circle_list
{
	char						*name;
	t_circle_list				*next;
	t_circle_list				*prev;
	__int128_t					mask;
};

/*
** CIRCLE LIST
*/

t_circle_list	*circle_list_new(char *name);
void			circle_list_addback(t_circle_list **alst, t_circle_list *new);
void			free_circle_list(t_circle_list *list, t_circle_list *head);
int				circle_list_pop(t_circle_list **cur);

#endif
