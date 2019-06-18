/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 21:03:03 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/18 15:06:36 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		is_export(void *data, __unused void *to_find)
{
	t_variable *variable;

	variable = data;
	if (variable->flag & EXPORT_VAR && variable->flag & SET_VAR)
		return (TRUE);
	return (FALSE);
}

int		copy_var(void *src, void *dest)
{
	t_variable *source;
	t_variable *destination;

	source = src;
	destination = dest;
	destination->name = ft_strdup(source->name);
	destination->data = ft_strdup(source->data);
	return (0);
}

void	variable_update(void *context, void *data)
{
	t_list 		*tmp_env;
	t_variable	*variable;

	tmp_env = context;
	variable = data;
	add_var(&tmp_env, variable->name, variable->data, variable->flag);
}

char	*variable_to_tab(void *data)
{
	t_variable	*variable;
	char		*str;

	variable = data;
	str = NULL;
	ft_asprintf(&str, "%s=%s", variable->name, variable->data);
	return (str);
}

char	**generate_env(t_registry *shell, t_list *local_env)
{
	char	**env;
	t_list	*tmp_env;

	tmp_env = ft_lstfilter(shell->intern, NULL, is_export, copy_var);
	ft_lstiter_ctx(local_env, tmp_env, variable_update);
	env = ft_lsttotab(tmp_env, variable_to_tab);
	ft_lstdel(&tmp_env, free_node);
	return (env);
}
