/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 12:57:21 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/20 03:50:24 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

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
		ft_dprintf(2, "42sh: OLDPWD is not set\n");
		return (NULL);
	}
	else if ((expanded = user_home(str + 1)) == NULL)
	{
		ft_dprintf(2, "42sh: No such user or directory\n");
		return (NULL);
	}
	return (expanded);
}

char		*tilde(t_list *intern_var, char *str)
{
	t_vector	*vector;
	char		*source;
	char		*expanded;
	uint32_t	i;

	i = 0;
	if (ft_strbeginswith(str, "~") == FALSE)
		return (ft_strdup(str));
	i = ft_strcspn(str, "/");
	str[i] = character_swap(str[i]);
	expanded = tilde_expansion(intern_var, str);
	str[i] = character_swap('\0');
	if (expanded == NULL)
		return (NULL);
	vector = vct_dups(str);
	vct_replace_string(vector, 0, i, expanded);
	source = ft_strdup(vct_get_string(vector));
	vct_del(&vector);
	return (source);
}
