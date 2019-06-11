/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:06:27 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/11 11:49:57 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int		set_shlvl(t_registry *shell)
{
	char		*shlvl;

	shlvl = get_var(shell->intern, "SHLVL");
	if (shlvl == NULL)
		shlvl = ft_strdup("1");
	else
	{
		shlvl = ft_itoa(ft_atoi(shlvl) + 1);
		if (shlvl == NULL)
			return (FAILURE);
	}
	add_var(&shell->intern, "SHLVL", shlvl, EXPORT_VAR | SET_VAR);
	ft_strdel(&shlvl);
	return (SUCCESS);
}

static t_list	*get_env(t_list **alst, char **env)
{
	t_list		*node;
	t_variable	variable;
	size_t		pos;

	if (*env == NULL)
		return (*alst);
	pos = ft_strcspn(*env, "=");
	variable.name = ft_strsub(*env, 0, pos);
	variable.data = ft_strdup(*env + pos + 1);
	variable.flag = SET_VAR | EXPORT_VAR;
	if (variable.name == NULL || variable.data == NULL)
	{
		ft_dprintf(2, "[ERROR] - Env malloc failed.\n");
		return (NULL);
	}
	if (!(node = ft_lstnew(&variable, sizeof(t_variable))))
	{
		ft_dprintf(2, "[ERROR] - Env malloc error.\n");
		return (NULL);
	}
	ft_lstaddback(alst, node);
	return (get_env(alst, ++env));
}

int8_t			set_environment(t_registry *shell, char **av, char **env)
{
	if (*av != NULL)
	{
		if (parse_arg(av, &shell->option) == FAILURE)
		{
			ft_strdel(&(shell->option.command_str));
			return (FAILURE);
		}
	}
	if ((shell->option.option & HELP_OPT) != FALSE)
	{
		shell_usage();
		ft_flush_memory();
		exit(0);
	}
	get_env(&shell->intern, env);
	shell->hash.bin = ft_hmap_init(HMAP_BIN_SIZE);
	shell->hash.blt = ft_hmap_init(HMAP_BLT_SIZE);
	generate_grammar();	//TEMP
	shell->cur_fd.in = 0;	//TEMP
	shell->cur_fd.out = 1;	//TEMP
	shell->cur_fd.err = 2;	//TEMP
	if (set_shlvl(shell) == FAILURE)
		return (FAILURE);
	hash_builtin(shell);
	if (shell->hash.blt.used == FALSE)
		ft_dprintf(shell->cur_fd.err, "Hashmap blt is empty.\n");
	return (SUCCESS);
}
