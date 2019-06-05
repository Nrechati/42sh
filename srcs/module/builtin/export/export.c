/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/05 10:02:18 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_option			get_option_export(char *s, t_option option)
{
	while (*s)
	{
		if (*s == 'p')
			option |= P_OPT;
		else
		{
			ft_dprintf(g_shell->cur_fd.err,
						"21sh: export: -%c: invalid option\n", *s);
			ft_dprintf(g_shell->cur_fd.err, EXPORT_USAGE);
			return (ERROR_OPT);
		}
		s++;
	}
	return (option);
}

static void			add_var_and_rehash(t_registry *shell,
						t_variable *variable)
{
	if (variable->data)
	{
		add_var(&shell->intern, variable->name, variable->data,
				EXPORT_VAR | SET_VAR);
		if (ft_strequ(variable->name, "PATH") == TRUE)
			ft_hmap_free_content(&(shell->hash.bin), ft_free);
	}
	else
	{
		variable->data = ft_strdup(get_var(shell->intern, variable->name));
		add_var(&shell->intern, variable->name, variable->data, EXPORT_VAR);
	}
}

static int8_t		export_process(t_registry *shell, char **av)
{
	t_variable	*variable;
	char		*equal;

	while (*av != NULL)
	{
		variable = (t_variable *)ft_malloc(sizeof(t_variable));
		if (variable == NULL)
			return (FAILURE);
		ft_bzero(variable, sizeof(t_variable));
		variable->name = ft_strdup(*av);
		if ((equal = ft_strchr(*av, '=')) != NULL)
		{
			equal = ft_strchr(variable->name, '=');
			*equal = '\0';
			variable->data = ft_strdup(ft_strchr(*av, '=') + 1);
		}
		add_var_and_rehash(shell, variable);
		free_node((void *)variable);
		av++;
	}
	return (SUCCESS);
}

int8_t				export_blt(t_registry *shell, char **av)
{
	t_option	option;

	av++;
	option = 0;
	if (((option |= set_options(&av, get_option_export)) == ERROR_OPT))
		return (FAILURE);
	if (*av == NULL)
	{
		print_lst(shell->intern, shell->cur_fd.out,
					(option & P_OPT) ? "export " : "", EXPORT_VAR);
	}
	return (export_process(shell, av));
}
