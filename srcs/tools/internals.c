/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:15:49 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/29 18:52:29 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char		*get_intern_var(t_registry *shell, char *name)
{
	return (get_data(shell->intern, name));
}

int8_t		add_intern_var(t_registry *shell, char *name, char *data,
				t_option flag)
{
	if (get_data(shell->intern, name) == NULL)
		return (create_node(&(shell->intern), name, data, flag));
	return (change_node(&(shell->intern), name, ft_strdup(data), flag));
}

int8_t		add_intern_nbr(t_registry *shell, char *name, int data,
				t_option flag)
{
	int8_t	ret;
	char	*data_copy;

	ret = SUCCESS;
	data_copy = NULL;
	data_copy = ft_itoa(data);
	ret = add_intern_var(shell, name, data_copy, flag);
	ft_strdel(&data_copy);
	return (ret);
}

size_t		list_export_size(t_list *lst)
{
	size_t		count;
	t_variable	*variable;

	count = 0;
	while (lst != NULL)
	{
		variable = (t_variable *)lst->data;
		if (variable->flag & EXPORT_VAR)
			count++;
		lst = lst->next;
	}
	return (count);
}

