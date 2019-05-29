/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:06:50 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/29 18:52:29 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void			print_lst(t_list **alst, int fd)
{
	t_list *ptr;

	if (alst == NULL)
		return ;
	ptr = *alst;
	while (ptr != NULL)
	{
		ft_dprintf(fd, "%s=%s\n", ((t_variable *)ptr->data)->name
				, ((t_variable *)ptr->data)->data, ptr->next);
		ptr = ptr->next;
	}
}

int8_t			create_node(t_list **alst, const char *name, const char *data,
					t_option flag)
{
	t_variable	variable;
	t_list		*newdir;

	if (name == NULL)
		return (FAILURE);
	ft_bzero(&variable, sizeof(t_variable));
	variable.name = ft_strdup(name);
	variable.data = ft_strdup(data);
	variable.flag = flag;
	if (variable.name == NULL || variable.data == NULL)
		return (FAILURE);
	if ((newdir = ft_lstnew(&variable, sizeof(t_variable))) == NULL)
		return (FAILURE);
	ft_lstaddback(alst, newdir);
	return (SUCCESS);
}

int8_t			change_node(t_list **alst, const char *name, char *data,
					t_option flag)
{
	t_list *ptr;

	ptr = *alst;
	if (name == NULL || data == NULL)
		return (FAILURE);
	while (ptr != NULL)
	{
		if (ft_strequ(((t_variable *)ptr->data)->name, name) == TRUE)
		{
			ft_free(((t_variable *)ptr->data)->data);
			((t_variable *)ptr->data)->data = data;
			((t_variable *)ptr->data)->flag = flag;
			return (SUCCESS);
		}
		ptr = ptr->next;
	}
	return (create_node(alst, name, data, flag));
}

char			*get_data(t_list *lst, char *name)
{
	t_list *node;

	if ((node = ft_lstfind(lst, name, find_variable)))
		return (((t_variable *)node->data)->data);
	return (NULL);
}
