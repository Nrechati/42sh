/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/15 11:43:00 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

uint8_t				type_blt(t_registry *shell, char **av)
{
	char		*path_bin;
	uint8_t		error;

	av++;
	error = SUCCESS;
	while (*av != NULL)
	{
		path_bin = NULL;
		if (ft_hmap_getdata(&shell->hash.blt, *av) != NULL)
			ft_printf("%s is a shell builtin\n", *av);
		else if ((path_bin = ft_hmap_getdata(&shell->hash.bin, *av)) != NULL)
			ft_printf("%s is hashed (%s)\n", *av, path_bin);
		else if (find_in_path(shell, *av, &path_bin) == SUCCESS)
			ft_printf("%s is %s\n", *av, path_bin);
		else
		{
			error = 1;
			ft_dprintf(STDERR_FILENO, "42sh: type: %s: not found\n", *av);
		}
		av++;
	}
	return (error);
}
