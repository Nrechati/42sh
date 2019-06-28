/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/15 11:32:54 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t				unset_blt(t_registry *shell, char **av)
{
	++av;
	if (*av == NULL)
	{
		ft_putendl_fd(UNSET_USAGE, STDERR_FILENO);
		return (FAILURE);
	}
	while (*av != NULL)
	{
		if (shell->intern != NULL)
			free_var(&shell->intern, *av);
		if (ft_strequ(*av, "PATH") == TRUE)
			ft_hmap_free_content(&(shell->hash.bin), ft_free);
		av++;
	}
	return (SUCCESS);
}
