/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:52:29 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t				unset_blt(t_registry *shell, char **av)
{
	++av;
	if (*av == NULL)
	{
		ft_dprintf(shell->cur_fd.err, UNSET_USAGE);
		return (FAILURE);
	}
	if (shell->intern == NULL)
		return (SUCCESS);
	free_var(&shell->intern, *av);
	if (ft_strequ(*av, "PATH") == TRUE)
		ft_hmap_free_content(&(shell->hash.bin), ft_free);
	return (SUCCESS);
}
