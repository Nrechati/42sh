/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/15 11:29:24 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>
#include <limits.h>

static char			*ft_get_curpath(t_registry *shell,
							const char *path_give_by_user)
{
	char	*home_path;
	char	*curpath;

	if (path_give_by_user == NULL)
	{
		home_path = get_var(shell->intern, "HOME");
		curpath = ft_strdup(home_path != NULL ? home_path : get_home_path());
	}
	else if (ft_strequ(path_give_by_user, "-") == TRUE)
	{
		if ((curpath = get_var(shell->intern, "OLDPWD")) == NULL)
			ft_dprintf(STDERR_FILENO, CD_ERROR_OLDPWD_NOTSET);
		else
			curpath = ft_strdup(curpath);
	}
	else if (*path_give_by_user == '/' || *path_give_by_user == '.')
		curpath = ft_strdup(path_give_by_user);
	else
	{
		if ((curpath = is_cdpath_env(shell, path_give_by_user)) == NULL)
			curpath = ft_strdup(path_give_by_user);
	}
	return (curpath);
}

static void			set_oldpwd_and_pwd(t_registry *shell, char *curpath,
						char *old_pwd, const t_option option)
{
	char		*pwd;

	if (option & P_OPT)
	{
		pwd = NULL;
		pwd = getcwd(NULL, PATH_MAX);
		add_var(&shell->intern, "PWD", pwd, SET_VAR | EXPORT_VAR);
		ft_strdel(&pwd);
	}
	else
		add_var(&shell->intern, "PWD", curpath, SET_VAR | EXPORT_VAR);
	add_var(&shell->intern, "OLDPWD", old_pwd, SET_VAR | EXPORT_VAR);
}

static uint8_t		change_directory(t_registry *shell, char *curpath,
						const char *path_give_by_user, const t_option option)
{
	char		*old_pwd;

	old_pwd = get_pwd(shell, NO_OPT);
	if (check_path(shell, curpath, path_give_by_user) == TRUE)
	{
		set_oldpwd_and_pwd(shell, curpath, old_pwd, option);
		if (ft_strequ(path_give_by_user, "-") == TRUE)
			ft_printf("%s\n", get_var(shell->intern, "PWD"));
		return (exit_cd(shell, &old_pwd, &curpath, SUCCESS));
	}
	return (exit_cd(shell, &old_pwd, &curpath, 1));
}

static int8_t		is_root(char *path)
{
	uint32_t	i;

	i = 0;
	if (path == NULL || path[0] == '\0')
		return (FALSE);
	while (path[i] != '\0')
	{
		if (path[i] != '/')
			return (FALSE);
		++i;
	}
	path[1] = '\0';
	return (TRUE);
}

uint8_t				cd_blt(t_registry *shell, char **av)
{
	char		*curpath;
	t_option	option;

	av++;
	ft_printf("erferfgerferg");
	ft_printf("av[1]: %s\n", *av);
	if (((option = set_options(&av, get_option_cd)) == ERROR_OPT)
		|| (curpath = ft_get_curpath(shell, *av)) == NULL
		|| one_only_arg(av) == FALSE)
		return (2);
	if (is_root(curpath) == FALSE && curpath[ft_strlen(curpath) - 1] == '/')
		curpath[ft_strlen(curpath) - 1] = '\0';
	if ((option & P_OPT) == FALSE)
	{
		if (*curpath != '/')
			if ((curpath = concat_pwd_with_curpath(shell, &curpath)) == NULL)
				return (3);
		if ((curpath = make_curpath_simple(curpath)) == NULL)
		{
			ft_dprintf(STDERR_FILENO, "42sh: cd: %s: %s", ft_strequ(*av,
					"-") ? get_var(shell->intern, "OLDPWD") : *av, NOFI);
			return (1);
		}
		else if (ft_strlen(curpath) + 1 >= PATH_MAX)
			curpath = get_relative_path(&curpath);
	}
	return (change_directory(shell, curpath, *av, option));
}
