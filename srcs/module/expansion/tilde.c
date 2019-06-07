/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 12:57:21 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/06 18:25:18 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>
/*
static char	*user_home(const char *str)
{
	char	*path;

	path = NULL;
	ft_asprintf(&path, "/Users/%s", str);
	if (access(path, F_OK) != SUCCESS)
	{
		ft_strdel(&path);
		return (NULL);
	}
	return (path);
}
*/
static char	*tilde_expansion(t_resolution *resolve, const char *str)
{
	char	*expanded;

	(void)resolve;
	(void)str;
	expanded = NULL;
/*	if (ft_strequ(str, "~") == TRUE)
		expanded = ft_strdup(get_var(resolve->env, "HOME"));
	else if (ft_strequ(str, "~+") == TRUE)
		expanded = ft_strdup(get_var(resolve->env, "PWD"));
	else if (ft_strequ(str, "~-") == TRUE)
	{
		if ((expanded = get_var(resolve->env, "OLDPWD")) != NULL)
			return (ft_strdup(expanded));
		ft_dprintf(2, "21sh: OLDPWD is not set\n");
		error_analyzer(resolve);
	}
	else if ((expanded = user_home(str + 1)) == NULL)
	{
		ft_dprintf(2, "21sh: No such user or directory\n");
		error_analyzer(resolve);
	}*/
	return (expanded);
}

char		*tilde(t_resolution *resolve, char *str)
{
	char		*expanded;
	char		*holder;
	uint32_t	i;

	i = 0;
	holder = NULL;
	if (ft_strnequ(str, "~/", 2) == FALSE && ft_strequ(str, "~") == FALSE)
		return (str);
	if (str[0] == '~')
	{
		i = ft_strcspn(str, "/");
		str[i] = character_swap(str[i]);
		expanded = tilde_expansion(resolve, str);
		str[i] = character_swap('\0');
		ft_asprintf(&holder, "%s%s", expanded, str + i);
		ft_strdel(&expanded);
		ft_strdel(&str);
		str = holder;
	}
	return (str);
}
