/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 14:03:25 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/15 11:42:52 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>
#include <limits.h>

char			*get_pwd(t_registry *shell, const t_option option)
{
	char	*pwd;
	char	*env_value_pwd;

	pwd = NULL;
	if ((option & P_OPT) == FALSE)
	{
		env_value_pwd = get_var(shell->intern, "PWD");
		if (env_value_pwd != NULL)
			pwd = ft_strdup(env_value_pwd);
		if (pwd == NULL || access(pwd, F_OK) != SUCCESS)
			pwd = getcwd(NULL, PATH_MAX);
	}
	else
		pwd = getcwd(pwd, PATH_MAX);
	if (pwd == NULL)
		ft_dprintf(STDERR_FILENO, "42sh: getcwd(): An error occurred\n");
	return (pwd);
}

t_option		get_option_pwd(char *s, t_option option)
{
	option = 0;
	while (*s)
	{
		if (*s == 'L')
			option |= L_OPT;
		else if (*s == 'P')
			option |= P_OPT;
		else
		{
			ft_dprintf(STDERR_FILENO,
					"42sh: pwd: -%c: invalid option\n", *s);
			ft_dprintf(STDERR_FILENO, "pwd: usage: pwd [-LP]\n");
			return (ERROR_OPT);
		}
		s++;
	}
	return (option);
}

int8_t			pwd_blt(t_registry *shell, char **av)
{
	t_option	option;
	char		*pwd;

	++av;
	option = set_options(&av, get_option_pwd);
	if (option == ERROR_OPT)
		return (FAILURE);
	pwd = get_pwd(shell, option);
	if (pwd == NULL)
		return (FAILURE);
	ft_putendl(pwd);
	ft_strdel(&pwd);
	return (SUCCESS);
}
