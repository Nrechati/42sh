/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_process_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:50:03 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/07 11:50:41 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t			get_process_type(t_registry *shell, t_process *process)
{
	int8_t		ret;
	char		*pathname;

	ret = 0;
	pathname = NULL;
	if (process->process_type & IS_ASSIGN)
		return (SUCCESS);
	if (ft_hmap_getdata(&shell->hash.blt, process->av[0]) != NULL)
		process->process_type |= IS_BLT;
	else if (ft_hmap_getdata(&shell->hash.bin, process->av[0]) != NULL)
		process->process_type |= IS_BIN;
	else if ((ret = find_in_path(shell, process->av[0], &pathname)) != NOT_FOUND)
	{
		if (ret == FAILURE)
			return (FAILURE);
		hash_one(shell, process->av[0], pathname);
		process->process_type |= IS_BIN;
	}
	else if (process->av[0][0] == '.' || process->av[0][0] == '/')
		process->process_type |= IS_ABS;
	else
		process->process_type |= IS_NOTFOUND;
	return (SUCCESS);
}
