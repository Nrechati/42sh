/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/02 14:42:17 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

uint8_t				unset_blt(t_registry *shell, char **av)
{
	uint8_t ret;

	++av;
	ret = SUCCESS;
	while (*av != NULL)
	{
		if (is_valid_variable(*av) == FALSE)
		{
			ft_dprintf(STDERR_FILENO,
					"42sh: unset: `%s': not a valid identifier\n", *av);
			ret = 2;
		}
		else if (shell->intern != NULL)
			free_var(&shell->intern, *av);
		if (ft_strequ(*av, "PATH") == TRUE)
			ft_hmap_free_content(&(shell->hash.bin), free);
		av++;
	}
	return (ret);
}
