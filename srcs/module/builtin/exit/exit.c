/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 11:59:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/29 15:40:50 by skuppers         ###   ########.fr       */
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

uint8_t			verif_arg(char *s)
{
	static char	*long_s = "-9223372036854775808";
	size_t		len;
	size_t		i;
	uint8_t		ok;

	ok = FALSE;
	i = s[0] == '-' ? 1 : 0;
	long_s += i == 1 ? 0 : 1;
	len = ft_strlen(s + i);
	while (s[i] != '\0' && long_s[i] != '\0' && ok != 2)
	{
		if (s[i] < '0' || s[i] > '9' || len > 19
				|| (len == 19 && ok == FALSE && long_s[i] < s[i]))
			ok = 2;
		else if (s[i] < long_s[i])
			ok = TRUE;
		i++;
	}
	if (ok == 2 || (s[0] == '-' && s[1] == '\0') || (i == 19 && s[18] >= '8'))
	{
		ft_dprintf(2, "42sh: exit: %s: numeric argument required\n", s);
		return (2);
	}
	return ((uint8_t)ft_atoi(s));
}

uint8_t			exit_blt(t_registry *shell, char **av)
{
	static uint8_t	job_notified;
	uint8_t			ret;

	if (shell->job_list != NULL && job_notified == 0)
	{
		job_notified = 1;
		ft_printf("You have active background jobs.\n");
		return (SUCCESS);
	}
	kill_active_jobs(shell);
	ft_printf("TM ret: %d\n", term_mode(TERMMODE_DFLT));
	if (av != NULL)
		++av;
	if (av != NULL && *av != NULL)
	{
		if (*(av + 1) != NULL)
		{
			ft_putendl_fd("42sh: exit: too many arguments", STDERR_FILENO);
			return (2);
		}
		ret = verif_arg(*av);
	}
	else
		ret = SUCCESS;
	ft_putendl_fd("exit", STDERR_FILENO);
	shell_exit_routine(shell, ret);
	return (SUCCESS); // Never reaches this point
}
