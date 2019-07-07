/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/06 17:57:20 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int8_t		find_type_path(t_registry *shell, char *arg)
{
	char		*path_bin;
	struct stat	stat;

	if (arg == NULL || *arg == '\0')
		return (FALSE);
	path_bin = NULL;
	if (lstat(arg, &stat) == SUCCESS && (stat.st_mode & S_IFDIR) == FALSE
			&& access(arg, X_OK) == SUCCESS)
	{
		if (*arg == '/' || ft_strnequ(arg, "./", 2) == TRUE)
			ft_printf("%s is %s\n", arg, arg);
		else
			ft_printf("%s is ./%s\n", arg, arg);
		return (SUCCESS);
	}
	else if (find_in_path(shell, arg, &path_bin) == SUCCESS)
	{
		ft_printf("%s is %s\n", arg, path_bin);
		ft_strdel(&path_bin);
		return (SUCCESS);
	}
	ft_strdel(&path_bin);
	return (FAILURE);
}

static int8_t		type_loop_arg(t_registry *shell, char *arg)
{
	char	*path_bin;

	path_bin = NULL;
	if (ft_hmap_getdata(&shell->hash.blt, arg) != NULL)
		ft_printf("%s is a shell builtin\n", arg);
	else if ((path_bin = ft_hmap_getdata(&shell->hash.bin, arg)) != NULL)
		ft_printf("%s is hashed (%s)\n", arg, path_bin);
	else if (find_type_path(shell, arg) == FAILURE)
	{
		ft_dprintf(STDERR_FILENO, "42sh: type: %s: not found\n", arg);
		return (1);
	}
	return (SUCCESS);
}

uint8_t				type_blt(t_registry *shell, char **av, t_process *process)
{
	uint8_t		error;
	int8_t		ret;

	av++;
	(void)process;
	error = SUCCESS;
	while (*av != NULL)
	{
		ret = type_loop_arg(shell, *av);
		if (ret == 1)
			error = 1;
		else if (ret == SUCCESS && write(1, NULL, 0) == FAILURE)
		{
			ft_putendl_fd("42sh: type: write error: Bad file descriptor", 2);
			return (1);
		}
		av++;
	}
	return (error);
}
