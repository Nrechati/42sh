/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_additions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/06 15:28:24 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>
#include <pwd.h>
#include <limits.h>

t_option		get_option_cd(char *s, t_option option)
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
					"21sh: cd: -%c: invalid option\n", *s);
			ft_dprintf(STDERR_FILENO, CD_USAGE);
			return (ERROR_OPT);
		}
		s++;
	}
	return (option);
}

uint8_t			exit_cd(t_registry *shell, char **old_pwd,
					char **curpath, uint8_t ret)
{
	(void)shell;
	ft_strdel(old_pwd);
	ft_strdel(curpath);
	return (ret);
}

char			*concat_pwd_with_curpath(t_registry *shell, char **path)
{
	char	*curpath;
	char	*pwd;
	char	*tmp_pwd;

	pwd = get_pwd(shell, NO_OPT);
	if (pwd == NULL)
		return (NULL);
	else if (pwd[ft_strlen(pwd) - 1] != '/')
	{
		tmp_pwd = pwd;
		pwd = ft_strjoin(pwd, "/");
		ft_strdel(&tmp_pwd);
	}
	curpath = ft_strjoin(pwd, *path);
	ft_strdel(path);
	ft_strdel(&pwd);
	return (curpath);
}

char			*get_home_path(t_registry *shell)
{
	struct passwd	*passwd;
	char			*user_name;
	char			*home_path;

	home_path = get_var(shell->intern, "HOME");
	if (home_path != NULL && *home_path != '\0')
		return (home_path);
	if ((user_name = get_var(g_shell->intern, "USER")) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "21sh: cd: USER variable is not set\n");
		return (NULL);
	}
	if ((passwd = getpwnam(user_name)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "21sh: cd: user `%s'is unknown\n", user_name);
		return (NULL);
	}
	home_path = passwd->pw_dir;
	if (home_path != NULL && *home_path != '\0')
		return (home_path);
	return (NULL);
}

char			*get_relative_path(char **curpath)
{
	char	*pwd;
	char	*new_path;

	pwd = NULL;
	pwd = getcwd(NULL, PATH_MAX);
	if (ft_strstr(*curpath, pwd) != NULL)
		new_path = ft_strdup(*curpath + ft_strlen(pwd) + 1);
	else
		return (*curpath);
	ft_strdel(curpath);
	return (new_path);
}
