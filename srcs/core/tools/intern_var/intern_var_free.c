/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intern_var_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:23:48 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/04 17:45:37 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void			clear_node(void *node)
{
	t_variable	*variable;

	variable = node;
	ft_free(variable->name);
	ft_free(variable->data);
}

void			free_anode(t_list *ptr)
{
	clear_node(ptr->data);
	ft_free(ptr->data);
}

int8_t			del_node(t_list *ptr, const char *name)
{
	t_list	*tmp;

	tmp = ptr;
	ptr = ptr->next;
	while (ptr != NULL)
	{
		if (ft_strequ(((t_variable *)ptr->data)->name, name) == TRUE)
		{
			tmp->next = ptr->next;
			free_anode(ptr);
			ft_free(ptr);
			return (SUCCESS);
		}
		tmp = tmp->next;
		ptr = ptr->next;
	}
	return (FAILURE);
}

int8_t			free_node(t_list **alst, const char *name)
{
	t_list		*ptr;
	t_variable	*env;

	ptr = *alst;
	env = (t_variable*)ptr->data;
	if (ft_strequ(env->name, name) == TRUE)
	{
		*alst = ptr->next;
		free_anode(ptr);
		ft_free(ptr);
		return (SUCCESS);
	}
	return (del_node(ptr, name));
}
