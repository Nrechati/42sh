/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 12:09:44 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/03 16:39:02 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

int8_t			hash_one(t_registry *shell, char *key, char *path)
{
	if (ft_hmap_insert(&(shell->hash.bin), key, path) == FALSE)
		return (FAILURE);
	return (SUCCESS);
}

static void		hash_dir(t_registry *shell, const char *dir)
{
	char			*asp;
	DIR				*dip;
	struct dirent	*dit;

	if ((dip = opendir(dir)) != NULL)
	{
		while ((dit = readdir(dip)) != NULL)
		{
			asp = NULL;
			ft_asprintf(&asp, "%s/%s", dir, dit->d_name);
			if (asp != NULL)
			{
				if (dit->d_name[0] != '.')
				{
					if (ft_hmap_insert(&(shell->hash.bin)
							, dit->d_name, asp) == FALSE)
						ft_free(asp);
				}
				else
					ft_free(asp);
			}
		}
		if (closedir(dip) == SUCCESS)
			return ;
	}
}

static int8_t	hash_all_path(t_registry *shell)
{
	uint32_t	i;
	char		**tabs;

	if (shell->hash.bin.used > 0)
		ft_hmap_free_content(&(shell->hash.bin), ft_free);
	if (get_var(shell->intern, "PATH") != NULL)
	{
		tabs = ft_strsplit(get_var(shell->intern, "PATH"), ":");
		if (tabs == NULL)
			return (FAILURE);
		i = 0;
		while (tabs[i] != NULL)
			hash_dir(shell, tabs[i++]);
		ft_freetab(&tabs);
	}
	return (SUCCESS);
}

void			hash_builtin(t_registry *shell)
{
	ft_hmap_insert(&(shell->hash.blt), "echo", echo_blt);
	ft_hmap_insert(&(shell->hash.blt), "cd", cd_blt);
	ft_hmap_insert(&(shell->hash.blt), "hash", hash_blt);
	ft_hmap_insert(&(shell->hash.blt), "exit", exit_blt);
	ft_hmap_insert(&(shell->hash.blt), "type", type_blt);
	ft_hmap_insert(&(shell->hash.blt), "export", export_blt);
	ft_hmap_insert(&(shell->hash.blt), "set", set_blt);
	ft_hmap_insert(&(shell->hash.blt), "unset", unset_blt);
	ft_hmap_insert(&(shell->hash.blt), "pwd", pwd_blt);
}

static int		hash_get_opt(int i, char **av, t_option *opt)
{
	int 	j;

	while (av[i] && av[i][0] == '-')
	{
		j = 1;
		while (av[i][j])
		{
			if (av[i][j] == 'r' && (*opt & H_WIPE) == FALSE)
				*opt |= H_WIPE;
			else if (av[i][j] == 'a' && (*opt & H_ALL) == FALSE)
				*opt |= H_ALL;
			else if (av[i][j] == 'h' && (*opt & H_HELP) == FALSE)
				*opt |= H_HELP;
			else
			{
				ft_dprintf(2, "%s%s%s", HASH_GENERAL_ERROR, av[i], HASH_INVALID_OPT);
				return (FAILURE);
			}
			j++;
		}
		i++;
	}
	return (i);
}

static void		hash_print_help(void)
{
	ft_printf("%s%s%s%s%s%s%s%s%s%s%s"
			, HASH_USAGE
			, HASH_HELP
			, HASH_H_WIPE
			, HASH_H_ALL
			, HASH_H_HELP
			, HASH_ORULE_1
			, HASH_ORULE_2
			, HASH_OPT_1
			, HASH_OPT_2
			, HASH_UTIL_1
			, HASH_UTIL_2);
}

static int16_t	hash_handle_opt(t_registry *shell, t_option opt)
{
	if (opt & H_HELP)
	{
		hash_print_help();
		return (H_HELP);
	}
	else if (opt & H_ALL)
	{
		hash_all_path(shell);
		return (H_ALL);
	}
	else if (opt & H_WIPE)
	{
		ft_hmap_free_content(&(shell->hash.bin), ft_free);
		return (H_WIPE);
	}
	else
		return (SUCCESS);
}

int8_t			hash_blt(t_registry *shell, char **av)
{
	int			i;
	t_option	opt;

	opt = 0;
	if (av == NULL)
	{
		ft_dprintf(2, "hash: NULL av given to built-in\n");
		return (FAILURE);
	}
	if (!av[1])
	{
		ft_simplified_hash_print(&(shell->hash.bin));
		return (SUCCESS);
	}
	if ((i = hash_get_opt(1, av, &opt)) == FAILURE)
		return (FAILURE);
	if (hash_handle_opt(shell, opt) == H_HELP)
		return (SUCCESS);
	return (SUCCESS);
}
