/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/11 11:51:39 by skuppers         ###   ########.fr       */
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
	if (shell->intern != NULL)
		free_node(&shell->intern, *av);
//read-only
	return (SUCCESS);
}
