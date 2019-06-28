/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_size_cb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:47:10 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/28 11:01:27 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <sys/stat.h>

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
	if (lstat(pathname, &stat) == FAILURE)
		return (ERROR);
	if (stat.st_size > 0)
		return (TRUE);
	return (FALSE);
}

uint8_t		test_z_cb(void *data, __unused void *more)
{
	char			*str;

	if (!data)
		return (ERROR);
	str = data;
	if (ft_strlen(str) == 0)
		return (TRUE);
	return (FALSE);
}
