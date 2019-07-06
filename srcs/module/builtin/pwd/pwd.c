/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 14:03:25 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/06 17:53:26 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>
#include <limits.h>

char			*get_pwd(t_registry *shell, const t_option option)
{
	const char	*env_value_pwd;
	char		*pwd;

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
		ft_putendl_fd("42sh: getcwd(): An error occurred", STDERR_FILENO);
	return (pwd);
}

t_option		get_option_pwd(char *s, t_option option)
{
	option = 0;
	while (*s != '\0')
	{
		if (*s == 'L')
			option |= L_OPT;
		else if (*s == 'P')
			option |= P_OPT;
		else
		{
			ft_dprintf(STDERR_FILENO,
					"42sh: pwd: -%c: invalid option\n", *s);
			ft_putendl_fd("pwd: usage: pwd [-LP]", STDERR_FILENO);
			return (ERROR_OPT);
		}
		s++;
	}
	return (option);
}

uint8_t			pwd_blt(t_registry *shell, char **av, t_process *process)
{
	t_option	option;
	char		*pwd;

	++av;
	(void)process;
	option = set_options(&av, get_option_pwd);
	if (option == ERROR_OPT)
		return (2);
	pwd = get_pwd(shell, option);
	if (pwd == NULL)
		return (1);
	ft_putendl(pwd);
	ft_strdel(&pwd);
	if (write(1, NULL, 0) == FAILURE)
	{
		ft_putendl_fd("42sh: pwd: write error: Bad file descriptor", 2);
		return (1);
	}
	return (SUCCESS);
}
