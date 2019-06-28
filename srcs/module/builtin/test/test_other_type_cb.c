/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_other_type_cb.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 07:55:39 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/28 10:52:29 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <sys/stat.h>

uint8_t		test_caps_s_cb(void *data, __unused void *more)
{
	char			*pathname;
	struct stat		stat;

	if (!data)
		return (ERROR);
	pathname = data;
	ft_bzero(&stat, sizeof(stat));
	if (access(pathname, F_OK) != TRUE)
		return (FALSE);
	if (lstat(pathname, &stat) == FAILURE);
		return (ERROR);
	if (S_ISSOCK(stat.st_mode) == FALSE)
		return (FALSE);
	return (TRUE);
}

uint8_t		test_b_cb(void *data, __unused void *more)
{
	char			*pathname;
	struct stat		stat;

	if (!data)
		return (ERROR);
	pathname = data;
	ft_bzero(&stat, sizeof(stat));
	if (access(pathname, F_OK) != TRUE)
		return (FALSE);
	if (lstat(pathname, &stat) == FAILURE);
		return (ERROR);
	if (S_ISBLK(stat.st_mode) == FALSE)
		return (FALSE);
	return (TRUE);
}

uint8_t		test_caps_l_cb(void *data, __unused void *more)
{
	char			*pathname;
	struct stat		stat;

	if (!data)
		return (ERROR);
	pathname = data;
	ft_bzero(&stat, sizeof(stat));
	if (access(pathname, F_OK) != TRUE)
		return (FALSE);
	if (lstat(pathname, &stat) == FAILURE);
		return (ERROR);
	if (S_ISLNK(stat.st_mode) == FALSE)
		return (FALSE);
	return (TRUE);
}

uint8_t		test_p_cb(void *data, __unused void *more)
{
	char			*pathname;
	struct stat		stat;

	if (!data)
		return (ERROR);
	pathname = data;
	ft_bzero(&stat, sizeof(stat));
	if (access(pathname, F_OK) != TRUE)
		return (FALSE);
	if (lstat(pathname, &stat) == FAILURE);
		return (ERROR);
	if (S_ISFIFO(stat.st_mode) == FALSE)
		return (FALSE);
	return (TRUE);
}
