/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 12:09:44 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/06 17:52:49 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

static int16_t	hash_handle_opt(t_registry *shell, t_option opt)
{
	if (opt & H_HELP)
	{
		if (hash_print_help() == FALSE)
			return (FAILURE);
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

static uint8_t	protect_no_input(char **av)
{
	if (av == NULL || av[0] == NULL)
	{
		ft_dprintf(2, "%s%s", HASH_GENERAL_ERROR, HASH_NO_AV);
		return (TRUE);
	}
	return (FALSE);
}

static uint8_t	check_no_args(t_registry *shell, char **av)
{
	if (av[1] == NULL)
	{
		if (write(1, NULL, 0) == FAILURE)
		{
			ft_putendl_fd("42sh: hash: write error: Bad file descriptor", 2);
			return (ERROR);
		}
		ft_simplified_hash_print(&(shell->hash.bin));
		return (TRUE);
	}
	return (FALSE);
}

static uint8_t	do_hash(t_registry *shell, char **av, int i)
{
	int8_t		ret;

	ret = hash_args(shell, av[i]);
	if (ret == NOT_FOUND)
		ft_dprintf(2, "%s%s%s", HASH_GENERAL_ERROR, av[i], HASH_NOT_FOUND);
	else if (ret == 1)
		return (1);
	i++;
	return (0);
}

uint8_t			hash_blt(t_registry *shell, char **av, t_process *process)
{
	int			i;
	int8_t		ret;
	t_option	opt;

	opt = 0;
	(void)process;
	if (protect_no_input(av) == TRUE)
		return (1);
	if ((ret = check_no_args(shell, av)) == TRUE)
		return (SUCCESS);
	if (ret == ERROR)
		return (1);
	if ((i = hash_get_opt(1, av, &opt)) == FAILURE)
		return (2);
	if ((ret = hash_handle_opt(shell, opt)) == H_HELP)
		return (2);
	if (ret == FAILURE)
		return (1);
	while (av[i] != NULL)
	{
		if (do_hash(shell, av, i) == 1)
			return (1);
		i++;
	}
	return (SUCCESS);
}
