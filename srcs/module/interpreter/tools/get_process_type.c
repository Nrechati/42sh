/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_process_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:50:03 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/06 12:50:29 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t			get_process_type(t_registry *shell, t_process *process)
{
	int8_t		ret;
	char		*pathname;
	uint8_t		type;

	ret = 0;
	type = 0;
	pathname = NULL;
	if (ft_hmap_getdata(&shell->hash.blt, process->av[0]) != NULL)
		type |= IS_BLT;
	else if (ft_hmap_getdata(&shell->hash.bin, process->av[0]) != NULL)
		type |= IS_BIN;
	else if ((ret = find_in_path(shell, process->av[0], &pathname)) != NOT_FOUND)
	{
		if (ret == FAILURE)
			return (FAILURE);
		hash_one(shell, process->av[0], pathname);
		type |= IS_BIN;
	}
	else if (process->av[0][0] == '.' || process->av[0][0] == '/')
		type |= IS_ABS;
	else
		return (NOT_FOUND);
	process->process_type |= type;
	return (SUCCESS);
}
