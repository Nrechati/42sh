/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:57 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:41:26 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

int8_t				echo_blt(t_registry *shell, char **av)
{
	t_option	option;

	++av;
	option = 0;
	while (ft_strequ("-n", *av) == TRUE)
	{
		option |= N_OPT;
		++av;
	}
	while (*av != NULL)
	{
		ft_putstr_fd(*av, shell->cur_fd.out);
		++av;
		if (*av != NULL)
			ft_putchar_fd(' ', shell->cur_fd.out);
	}
	if ((option & N_OPT) == FALSE)
		ft_putchar_fd('\n', shell->cur_fd.out);
	return (SUCCESS);
}
