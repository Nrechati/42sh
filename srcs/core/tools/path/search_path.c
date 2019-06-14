/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 13:51:48 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/06 11:29:51 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>
#include <sys/stat.h>

static uint8_t			ft_exists_and_is_exec(char *path)
{
	struct stat		tmp;

	if (access(path, F_OK) == FAILURE)
		return (FALSE);
	if (stat(path, &tmp) == SUCCESS)
	{
		if (S_ISREG(tmp.st_mode) && access(path, X_OK) == SUCCESS)
			return (TRUE);
	}
	return (FALSE);
}

static int8_t			find_bin(char *path, char *bin, char **buf)
{
	ft_asprintf(buf, "%s/%s", path, bin);
	if (*buf == NULL)
	{
		ft_dprintf(2, HASH_GENERAL_ERROR HASH_MALLOC_ERROR);
		return (FAILURE);
	}
	if (ft_exists_and_is_exec(*buf) == TRUE)
		return (SUCCESS);
	ft_strdel(buf);
	return (NOT_FOUND);
}

int8_t					find_in_path(t_registry *shell, char *bin, char **buf)
{
	uint32_t	i;
	int8_t		ret;
	char		**tab;

	if (get_var(shell->intern, "PATH") == NULL)
		return (NOT_FOUND);
	tab = ft_strsplit(get_var(shell->intern, "PATH"), ":");
	if (tab == NULL)
	{
		ft_dprintf(2, HASH_GENERAL_ERROR HASH_MALLOC_ERROR);
		return (FAILURE);
	}
	i = 0;
	while (tab[i] != NULL)
	{
		ret = find_bin(tab[i], bin, buf);
		if (ret != NOT_FOUND)
			break;
		i++;
	}
	ft_freetab(&tab);
	return (ret);
}
