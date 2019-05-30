/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 12:09:44 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 19:06:21 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

static void		hash_bin(t_registry *shell, const char *bin)
{
	char			*asp;
	DIR				*dip;
	struct dirent	*dit;

	if ((dip = opendir(bin)) != NULL)
	{
		while ((dit = readdir(dip)) != NULL)
		{
			asp = NULL;
			ft_asprintf(&asp, "%s/%s", bin, dit->d_name);
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

static void		hash_builtin(t_registry *shell)
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

int8_t			hash_blt(t_registry *shell, char **av)
{
	uint32_t		i;
	char			**tabs;

	(void)av;
	if (shell->hash.bin.used > 0)
		ft_hmap_free_content(&(shell->hash.bin), ft_free);
	if (get_var(shell->intern, "PATH") != NULL)
	{
		tabs = ft_strsplit(get_var(shell->intern, "PATH"), ":");
		if (tabs == NULL)
			return (FAILURE);
		i = 0;
		while (tabs[i] != NULL)
			hash_bin(shell, tabs[i++]);
		ft_freetab(&tabs);
	}
	hash_builtin(shell);
	if (shell->hash.blt.used == FALSE)
		ft_dprintf(shell->cur_fd.err, "Hashmap blt is empty.\n");
	return (SUCCESS);
}
