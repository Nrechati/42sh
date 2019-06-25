/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 11:59:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/25 16:07:30 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t			exit_blt(t_registry *shell, char **av)
{
	int		ret;

	if (shell->job_list != NULL)
	{
		ft_printf("They are stopped jobs.\n");
		return (FAILURE);
	}
	++av;
	if (*av != NULL)
	{
		if (ft_isnumeric(*av) == FALSE)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			ft_putendl_fd("42sh: exit: %s: numeric argument required",
					STDERR_FILENO);
			shell_exit_routine(shell);
			exit(FAILURE);
		}
		else if (*(av + 1) != NULL)
		{
			ft_putendl_fd("42sh: exit: too many argument", STDERR_FILENO);
			return (1);
		}
	}
	ret = *av == NULL ? SUCCESS : ft_atoi(*av);
	shell_exit_routine(shell);
	ft_flush_memory();
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(ret);
}
