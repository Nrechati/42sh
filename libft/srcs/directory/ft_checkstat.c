/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkstat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 00:24:46 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:41:26 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "directory.h"
#include "ft_printf.h"

int			ft_checkstat(char *file, mode_t st_mode)
{
	t_stat	info;
	char	*path;

	path = NULL;
	if (*file == '/')
	{
		if (lstat(file, &info) < 0)
			return (-1);
	}
	else
	{
		ft_asprintf(&path, "./%s", file);
		if (path == NULL || lstat(file, &info) < 0)
			return (-1);
		ft_strdel(&path);
	}
	return (info.st_mode & st_mode);
}
