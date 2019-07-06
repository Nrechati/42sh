/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 11:50:45 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/06 18:00:32 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

uint8_t				unsetenv_blt(t_registry *shell, char **av, t_process *process)
{
	uint8_t		ret;

	++av;
	(void)process;
	ret = SUCCESS;
	while (*av != NULL)
	{
		if (is_valid_variable(*av) == FALSE)
		{
			ft_dprintf(STDERR_FILENO,
					"42sh: unsetenv: `%s': not a valid identifier\n", *av);
			ret = 2;
		}
		else if (shell->intern != NULL)
		{
			if (get_var_status(shell->intern, *av) & EXPORT_VAR)
				free_var(&shell->intern, *av);
		}
		if (ft_strequ(*av, "PATH") == TRUE)
			ft_hmap_free_content(&(shell->hash.bin), free);
		av++;
	}
	return (ret);
}
