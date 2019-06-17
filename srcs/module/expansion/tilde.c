/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 12:57:21 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/17 14:52:55 by skuppers         ###   ########.fr       */
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

static char	*tilde_expansion(t_list *intern_var, const char *str)
{
	char	*expanded;

	expanded = NULL;
	if (ft_strequ(str, "~") == TRUE || ft_strequ(str, "~/"))
		expanded = ft_strdup(get_var(intern_var, "HOME"));

	else if (ft_strequ(str, "~+") == TRUE)
		expanded = ft_strdup(get_var(intern_var, "PWD"));

	else if (ft_strequ(str, "~-") == TRUE)
	{
		if ((expanded = get_var(intern_var, "OLDPWD")) != NULL)
			return (ft_strdup(expanded));

		ft_dprintf(2, "21sh: OLDPWD is not set\n");

		return (NULL);
	}
	else if ((expanded = user_home(str + 1)) == NULL)
	{
		ft_dprintf(2, "21sh: No such user or directory\n");
		return (NULL);
	}

	return (expanded);
}

void		tilde(t_list *intern_var, char **str)
{
	t_vector	*vector;
	char		*string;


	char		*expanded;
	char		*holder;
	uint32_t	i;

	i = 0;
	holder = NULL;

	string = *str;

	if (ft_strbeginswith(string, "~") == FALSE)
		return ;
	vector = vct_dups(string);

	expanded = tilde_expansion(intern_var, string);

		str[i] = character_swap('\0');
		ft_asprintf(&holder, "%s%s", expanded, str + i);
		ft_strdel(&expanded);
		ft_strdel(&str);
		str = holder;

	return (str);
}*/
