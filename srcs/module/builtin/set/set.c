/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:23:09 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/06 17:53:54 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

uint8_t				set_blt(t_registry *shell, char **av, t_process *process)
{
	av++;
	(void)process;
	if (*av == NULL)
	{
		if (write(1, NULL, 0) == FAILURE)
		{
			ft_putendl_fd("42sh: set: write error: Bad file descriptor", 2);
			return (1);
		}
		print_lst(shell->intern, STDOUT_FILENO, "", SET_VAR);
	}
	return (SUCCESS);
}
