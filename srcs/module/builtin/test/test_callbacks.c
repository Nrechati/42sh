/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_callbacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 07:55:39 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/28 10:20:19 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <sys/stat.h>

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

uint8_t		test_c_cb(void *data, __unused void *more)
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
	if (S_ISCHR(stat.st_mode) == FALSE)
		return (FALSE);
	return (TRUE);
}

uint8_t		test_d_cb(void *data, __unused void *more)
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
	if (S_ISDIR(stat.st_mode) == FALSE)
		return (FALSE);
	return (TRUE);
}

uint8_t		test_e_cb(void *data, __unused void *more)
{
	char			*pathname;

	if (!data)
		return (ERROR);
	pathname = data;
	if (access(pathname, F_OK) == TRUE)
		return (TRUE);
	return (FALSE);
}

uint8_t		test_f_cb(void *data, __unused void *more)
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
	if (S_ISREG(stat.st_mode) == FALSE)
		return (FALSE);
	return (TRUE);
}

uint8_t		test_f_cb(void *data, __unused void *more)
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
	if (S_ISREG(stat.st_mode) == FALSE)
		return (FALSE);
	return (TRUE);
}

uint8_t		test_g_cb(void *data, __unused void *more)
{

}

uint8_t		test_L_cb(void *data, __unused void *more)
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

uint8_t		test_r_cb(void *data, __unused void *more)
{

}

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

uint8_t		test_s_cb(void *data, __unused void *more)
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
	if (stat.st_size > 0)
		return (TRUE);
	return (FALSE);
}

uint8_t		test_u_cb(void *data, __unused void *more)
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
	if (stat.st_mode & S_ISUID)
		return (TRUE);
	return (FALSE);
}

uint8_t		test_w_cb(void *data, __unused void *more)
{
	char			*pathname;

	if (!data)
		return (ERROR);
	pathname = data;
	ft_bzero(&stat, sizeof(stat));
	if (access(pathname, F_OK) != TRUE)
		return (FALSE);
	if (lstat(pathname, &stat) == FAILURE);
		return (ERROR);
	if (S_ISREG(stat.st_mode) == FALSE)
		return (FALSE);
	return (FALSE);
}
