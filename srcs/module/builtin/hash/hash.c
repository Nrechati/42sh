/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 12:09:44 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/03 16:26:18 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

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
	ft_hmap_insert(&(shell->hash.blt), "fc", fc_blt);
	ft_hmap_insert(&(shell->hash.blt), "fg", fg_blt);
	ft_hmap_insert(&(shell->hash.blt), "bg", bg_blt);
	ft_hmap_insert(&(shell->hash.blt), "jobs", jobs_blt);
	ft_hmap_insert(&(shell->hash.blt), "test", test_blt);
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
		ft_hmap_free_content(&(shell->hash.bin), free);
		shell->hash.bin.print_pad = 0;
		return (H_WIPE);
	}
	else
		return (SUCCESS);
}

uint8_t			hash_blt(t_registry *shell, char **av)
{
	int			i;
	int8_t		ret;
	t_option	opt;

	opt = 0;
	if (av == NULL || av[0] == NULL)
	{
		ft_dprintf(2, "%s%s"HASH_GENERAL_ERROR HASH_NO_AV);
		return (1);
	}
	else if (av[1] == NULL)
	{
		ft_simplified_hash_print(&(shell->hash.bin));
		return (SUCCESS);
	}
	if ((i = hash_get_opt(1, av, &opt)) == FAILURE)
		return (2);
	if (hash_handle_opt(shell, opt) == H_HELP)
		return (2);
	while (av[i] != NULL)
	{
		ret = hash_args(shell, av[i]);
		if (ret == NOT_FOUND)
			ft_dprintf(2, "%s%s%s" HASH_GENERAL_ERROR, av[i], HASH_NOT_FOUND);
		else if (ret == 1)
			return (1);
		i++;
	}
	return (SUCCESS);
}
