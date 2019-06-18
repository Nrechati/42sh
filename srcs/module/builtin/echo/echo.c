/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:57 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/15 11:34:26 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t				echo_blt(t_registry *shell, char **av)
{
	t_option	option;

	++av;
	(void)shell;
	option = 0;
	while (ft_strequ("-n", *av) == TRUE)
	{
		option |= N_OPT;
		++av;
	}
	while (*av != NULL)
	{
		ft_putstr(*av);
		++av;
		if (*av != NULL)
			ft_putchar(' ');
	}
	if ((option & N_OPT) == FALSE)
		ft_putchar('\n');
	return (SUCCESS);
}
