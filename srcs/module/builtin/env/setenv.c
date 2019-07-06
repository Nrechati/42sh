/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 12:08:41 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/06 13:48:29 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

uint8_t				setenv_blt(t_registry *shell, char **av)
{
	int			ac;
	uint8_t		ret;

	ret = SUCCESS;
	ac = ft_tabsize(av);
	if (ac != 3)
	{
		ft_dprintf(STDERR_FILENO, "21sh: setenv: Wrong number of arguments\n");
		ft_dprintf(STDERR_FILENO, "[USAGE]: setenv [name] [data]\n");
		ret = 2;
	}
	else if (is_valid_variable(*av) == FALSE)
	{
		ft_dprintf(STDERR_FILENO,
				"21sh: setenv: `%s': not a valid identifier\n", *av);
		ret = 2;
	}
	else
	{
		if (add_var(&shell->intern, av[1], av[2]
				, SET_VAR | EXPORT_VAR) == FAILURE)
			ret = 2;
		if (ft_strequ(*av, "PATH") == TRUE)
			ft_hmap_free_content(&(shell->hash.bin), free);
	}
	return (ret);
}
