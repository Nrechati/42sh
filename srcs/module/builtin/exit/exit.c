/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 11:59:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/02 19:28:01 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

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

static uint8_t	job_notified(t_registry *shell)
{
	if (shell->job_list != NULL && shell->job_notified == 0)
	{
		shell->job_notified++;
		ft_dprintf(2, "There are stopped jobs.\n");
		return (FALSE);
	}
	else
		return (TRUE);
}

uint8_t			exit_blt(t_registry *shell, char **av)
{
	uint8_t			ret;

	if (job_notified(shell) == FALSE)
		return (SUCCESS);
	if (av == NULL)
		shell_exit_routine(shell, SUCCESS);
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
	shell_exit_routine(shell, shell == NULL ? 0 : 
							ft_atoi(get_var(shell->intern, "?")));
	return (SUCCESS);
}
