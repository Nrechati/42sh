/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_other_type_cb.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 07:55:39 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/01 11:32:20 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <sys/stat.h>

uint8_t		test_caps_s_cb(void *data, __unused void *more, uint8_t type)
{
	char			*pathname;
	struct stat		stat;

	if (type == BINARY_OP)
	{
		ft_dprintf(2, "42sh: test: -S: binary operator expected\n", type);
		return (ERROR);
	}
	if (!data)
		return (ERROR);
	pathname = data;
	ft_bzero(&stat, sizeof(stat));
	if (access(pathname, F_OK) != TRUE)
		return (FALSE);
	if (lstat(pathname, &stat) == FAILURE)
		return (ERROR);
	if (S_ISSOCK(stat.st_mode) == FALSE)
		return (FALSE);
	return (TRUE);
}

uint8_t		test_b_cb(void *data, __unused void *more, uint8_t type)
{
	char			*pathname;
	struct stat		stat;

	if (type == BINARY_OP)
	{
		ft_dprintf(2, "42sh: test: -b: binary operator expected\n", type);
		return (ERROR);
	}
	if (!data)
		return (ERROR);
	pathname = data;
	ft_bzero(&stat, sizeof(stat));
	if (access(pathname, F_OK) != TRUE)
		return (FALSE);
	if (lstat(pathname, &stat) == FAILURE)
		return (ERROR);
	if (S_ISBLK(stat.st_mode) == FALSE)
		return (FALSE);
	return (TRUE);
}

uint8_t		test_caps_l_cb(void *data, __unused void *more, uint8_t type)
{
	char			*pathname;
	struct stat		stat;

	if (type == BINARY_OP)
	{
		ft_dprintf(2, "42sh: test: -L: binary operator expected\n", type);
		return (ERROR);
	}
	if (!data)
		return (ERROR);
	pathname = data;
	ft_bzero(&stat, sizeof(stat));
	if (access(pathname, F_OK) != TRUE)
		return (FALSE);
	if (lstat(pathname, &stat) == FAILURE)
		return (ERROR);
	if (S_ISLNK(stat.st_mode) == FALSE)
		return (FALSE);
	return (TRUE);
}

uint8_t		test_p_cb(void *data, __unused void *more, uint8_t type)
{
	char			*pathname;
	struct stat		stat;

	if (type == BINARY_OP)
	{
		ft_dprintf(2, "42sh: test: -p: binary operator expected\n", type);
		return (ERROR);
	}
	if (!data)
		return (ERROR);
	pathname = data;
	ft_bzero(&stat, sizeof(stat));
	if (access(pathname, F_OK) != TRUE)
		return (FALSE);
	if (lstat(pathname, &stat) == FAILURE)
		return (ERROR);
	if (S_ISFIFO(stat.st_mode) == FALSE)
		return (FALSE);
	return (TRUE);
}
