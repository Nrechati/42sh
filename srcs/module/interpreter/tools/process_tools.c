/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 04:44:46 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/05 15:38:23 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	remove_empty(char **av)
{
	char		*holder;
	int			index;

	holder = NULL;
	index = 0;
	while (av[index + 1])
	{
		holder = av[index + 1];
		av[index + 1] = av[index];
		av[index] = holder;
		index++;
	}
	ft_strdel(&av[index]);
}

int		expand_process(t_list *intern, t_process *process)
{
	int		index;
	char	*holder;

	if (process->type & IS_ASSIGN)
		return (SUCCESS);
	index = 0;
	holder = NULL;
	while (process->av[index])
	{
		if ((holder = expansion_pipeline(intern, process->av[index])) == NULL)
			return (FAILURE);
		if (*holder == '\0')
		{
			remove_empty(&process->av[index]);
			ft_strdel(&holder);
			continue;
		}
		ft_strdel(&process->av[index]);
		process->av[index++] = holder;
	}
	return (SUCCESS);
}

int8_t	is_path_to_bin(char *cmd)
{
	if (cmd[0] == '/')
		return (TRUE);
	else if (ft_strnequ("./", cmd, 2))
		return (TRUE);
	else if (ft_strnequ("../", cmd, 3))
		return (TRUE);
	else
		return (FALSE);
}

int8_t	get_process_type(t_registry *shell, t_process *process)
{
	int8_t		ret;
	char		*path;

	path = NULL;
	if (process->type & IS_ASSIGN || !process->av || process->av[0] == NULL)
		return (SUCCESS);
	if (ft_hmap_getdata(&shell->hash.blt, process->av[0]) != NULL)
		process->type |= IS_BLT;
	else if (ft_hmap_getdata(&shell->hash.bin, process->av[0]) != NULL)
		process->type |= IS_BIN;
	else if ((ret = find_in_path(shell, process->av[0], &path)) != NOT_FOUND)
	{
		if (ret == FAILURE)
			return (FAILURE);
		hash_one(shell, process->av[0], path);
		process->type |= IS_BIN;
	}
	else if (is_path_to_bin(process->av[0]) == TRUE)
		process->type |= IS_ABS;
	else
		process->type |= IS_NOTFOUND;
	return (SUCCESS);
}
