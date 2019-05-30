/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intern_var_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:06:50 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/29 18:52:29 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		find_variable(void *data, void *to_find)
{
	t_variable	*variable;
	char		*name;

	name = to_find;
	variable = data;
	return (ft_strequ(variable->name, name));
}

void			print_lst(t_list *lst, int fd, char *prefix, t_option flag)
{
	t_variable	*variable;

	while (lst != NULL)
	{
		variable = (t_variable *)lst->data;
		if (variable->flag & flag)
			ft_dprintf(fd, "%s%s=%s\n", prefix, variable->name, variable->data);
		lst = lst->next;
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
