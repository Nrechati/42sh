/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 11:59:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/27 21:50:51 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void			kill_active_jobs(t_registry *shell)
{
	t_list	*job_lst;

	if (shell->job_list == NULL)
		return ;
	job_lst = shell->job_list;
	while (job_lst != NULL)
	{
		kill(((t_job*)job_lst->data)->pgid, SIGKILL);
		job_lst = job_lst->next;
	}
}

int8_t			exit_blt(t_registry *shell, char **av)
{
	static uint8_t	job_notified;
	int				ret;

	if (shell->job_list != NULL && job_notified == 0)
	{
		job_notified = 1;
		ft_printf("You have active background jobs.\n");
		return (FAILURE);
	}
	kill_active_jobs(shell);
	term_mode(TERMMODE_DFLT);

	++av;
	if (*av != NULL)
	{
		if (ft_isnumeric(*av) == FALSE)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			ft_putendl_fd("42sh: exit: %s: numeric argument required",
					STDERR_FILENO);
			shell_exit_routine(shell, FAILURE);
			return (FAILURE); // Never reaches this point
		}
		else if (*(av + 1) != NULL)
		{
			ft_putendl_fd("42sh: exit: too many argument", STDERR_FILENO);
			return (1);
		}
	}
	ret = *av == NULL ? SUCCESS : ft_atoi(*av);
	ft_putendl_fd("exit", STDERR_FILENO);
	shell_exit_routine(shell, ret);
	return (SUCCESS); // Never reaches this point
}
//// into calling function:
////	if exit returned value is '1',
////	free process list and
////	call 'shell_exit_routine(shell, ret)
