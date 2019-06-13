/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 12:09:44 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/11 11:50:52 by skuppers         ###   ########.fr       */
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
		shell->hash.bin.print_pad = 0;
		return (H_WIPE);
	}
	else
		return (SUCCESS);
}

int8_t			hash_blt(t_registry *shell, char **av)
{
	int			i;
	int8_t		ret;
	t_option	opt;

	opt = 0;
	if (av == NULL)
	{
		ft_dprintf(2, HASH_GENERAL_ERROR HASH_NO_AV);
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
	while (av[i])
	{
		ret = hash_args(shell, av[i]);
		if (ret == NOT_FOUND)
			ft_dprintf(2, HASH_GENERAL_ERROR "%s" HASH_NOT_FOUND, av[i]);
		else if (ret == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
