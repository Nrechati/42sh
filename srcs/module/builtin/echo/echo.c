/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:57 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/06 17:49:05 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

uint8_t				echo_blt(t_registry *shell, char **av, t_process *process)
{
	t_option	option;
	int8_t		ret;

	++av;
	(void)shell;
	(void)process;
	option = 0;
	ret = SUCCESS;
	while (ft_strequ("-n", *av) == TRUE)
	{
		option |= N_OPT;
		++av;
	}
	while (*av != NULL)
	{
		ret = ft_putstr(*av);
		++av;
		if (*av != NULL)
			ret = ft_putstr(" ");
	}
	if ((option & N_OPT) == FALSE)
		ret = ft_putstr("\n");
	if (ret == FAILURE)
		ft_putendl_fd("42sh: echo: write error: Bad file descriptor", 2);
	return (ret == FAILURE ? 1 : SUCCESS);
}
