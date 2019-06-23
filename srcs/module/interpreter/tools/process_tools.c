/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 04:44:46 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/20 04:47:49 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		expand_process(t_list *intern, char **av)
{
	int		index;
	char	*holder;

	if (av == NULL)
		return (0);
	index = 0;
	holder = NULL;
	while(av[index])
	{
		if ((holder = expansion_pipeline(intern, av[index])) == NULL)
			return (-1);
		ft_strdel(&av[index]);
		av[index++] = holder;
	}
	return (0);
}

int8_t	get_process_type(t_registry *shell, t_process *process)
{
	int8_t		ret;
	char		*pathname;

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
