/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/15 11:32:54 by ffoissey         ###   ########.fr       */
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
		if (ft_isdigit(av[0][0]) == TRUE || multi_strchr("!?$-=", *av) == TRUE)
		{
			ft_dprintf(STDERR_FILENO,
					"42sh: unset: `%s': not a valid identifier\n", *av);
			ret = 2;
		}
		else if (shell->intern != NULL)
			free_var(&shell->intern, *av);
		if (ft_strequ(*av, "PATH") == TRUE)
			ft_hmap_free_content(&(shell->hash.bin), ft_free);
		av++;
	}
	return (ret);
}
