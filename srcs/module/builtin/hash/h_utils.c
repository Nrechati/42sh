/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:02:35 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/04 14:52:02 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

int8_t			hash_one(t_registry *shell, char *key, char *path)
{
	if (ft_hmap_insert(&(shell->hash.bin), key, path) == FALSE)
		return (FAILURE);
	return (SUCCESS);
}

int8_t			hash_args(t_registry *shell, char *key)
{
	int8_t	ret;
	char	*pathname;

	pathname = NULL;
	if ((ret = find_in_path(shell, key, &pathname)) == SUCCESS)
	{
		ret = hash_one(shell, key, pathname);
		if (ret == FAILURE)
			ft_strdel(&pathname);
	}
	return (ret);
}

void			hash_print_help(void)
{
	ft_printf("%s%s%s%s%s%s%s%s%s%s%s"
			, HASH_USAGE
			, HASH_HELP
			, HASH_H_WIPE
			, HASH_H_ALL
			, HASH_H_HELP
			, HASH_ORULE_1
			, HASH_ORULE_2
			, HASH_OPT_1
			, HASH_OPT_2
			, HASH_UTIL_1
			, HASH_UTIL_2);
}
