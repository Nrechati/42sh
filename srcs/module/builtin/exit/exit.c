/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 11:59:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/04 17:52:56 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void		free_opt(t_opt option)
{
	ft_strdel(&option.command_str);
}

static void		free_hash(t_hash hashmap, void (*del)(void *))
{
	ft_hmap_free_content(&hashmap, del);
	ft_free(hashmap.map);
	hashmap.map = NULL;
}

void			free_registry(t_registry *shell)
{
	free_opt(shell->option);
	ft_lstdel(&shell->intern, clear_node);
	free_hash(shell->hash.bin, ft_free);
	free_hash(shell->hash.blt, NULL);
}

int8_t			exit_blt(t_registry *shell, char **av)
{
	int		ret;

	++av;
	if (*av != NULL)
	{
		if (ft_isnumeric(*av) == FALSE)
		{
			ft_dprintf(shell->cur_fd.err,
					"21sh: exit: %s: numeric argument required\n", *av);
			free_registry(shell);
			ft_flush_memory();
			exit(FAILURE);
		}
		else if (*(av + 1) != NULL)
		{
			ft_dprintf(shell->cur_fd.err, "21sh: exit: too many argument\n");
			return (1);
		}
	}
	ret = *av == NULL ? SUCCESS : ft_atoi(*av);
	free_registry(shell);
	ft_flush_memory();
	exit(ret);
}
