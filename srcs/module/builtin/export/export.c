/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/17 14:29:01 by cempassi         ###   ########.fr       */
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

static void			export_var(t_registry *shell, t_variable *variable)
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
		if ((variable->data = get_var(shell->intern, variable->name)) == NULL)
			add_var(&shell->intern, variable->name, ft_strdup("\0"), EXPORT_VAR);
		else
		{
			variable->data = ft_strdup(variable->data);
			add_var(&shell->intern, variable->name, variable->data,
					SET_VAR | EXPORT_VAR);
		}
	}
}

static void			get_name_and_data(t_variable *variable, char *arg)
{
	char		*equal;

	variable->name = ft_strdup(arg);
	variable->data = NULL;
	if ((equal = ft_strchr(arg, '=')) != NULL)
	{
		equal = ft_strchr(variable->name, '=');
		*equal = '\0';
		variable->data = ft_strdup(ft_strchr(arg, '=') + 1);
	}
}

static int8_t		export_process(t_registry *shell, char **av)
{
	t_variable	*variable;

	while (*av != NULL)
	{
		variable = (t_variable *)ft_malloc(sizeof(t_variable));
		if (variable == NULL)
			return (FAILURE);
		get_name_and_data(variable, *av);
		export_var(shell, variable);
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
