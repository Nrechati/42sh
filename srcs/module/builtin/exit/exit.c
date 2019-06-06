/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 11:59:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/06 16:15:15 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

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
			shell_exit_routine(shell);
			exit(FAILURE);
		}
		else if (*(av + 1) != NULL)
		{
			ft_dprintf(shell->cur_fd.err, "21sh: exit: too many argument\n");
			return (1);
		}
	}
	ret = *av == NULL ? SUCCESS : ft_atoi(*av);
	shell_exit_routine(shell);
	ft_flush_memory();
	exit(ret);
}
