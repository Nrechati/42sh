/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_opt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:02:29 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/04 14:05:03 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

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

int8_t		hash_all_path(t_registry *shell)
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

int			hash_get_opt(int i, char **av, t_option *opt)
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