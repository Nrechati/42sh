/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intern_var_manager.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:15:49 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/29 18:52:29 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int			find_variable(void *data, void *to_find)
{
	t_variable	*variable;
	char		*name;

	name = to_find;
	variable = data;
	return (ft_strequ(variable->name, name));
}

char		*get_var(t_list *intern, char *name)
{
	t_list *node;

	if ((node = ft_lstfind(intern, name, find_variable)))
		return (((t_variable *)node->data)->data);
	return (NULL);
}

int8_t		add_var(t_list **intern, char *name, char *data, t_option flag)
{
	if (get_var(*intern, name) == NULL)
		return (create_node(intern, name, data, flag));
	return (change_node(intern, name, ft_strdup(data), flag));
}

int8_t		add_nbr_var(t_list **intern, char *name, int data, t_option flag)
{
	char	*data_str;
	int8_t	ret;

	data_str = ft_itoa(data);
	ret = add_var(intern, name, data_str, flag);
	ft_strdel(&data_str);
	return (ret);
}
