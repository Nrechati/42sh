/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:03:06 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/06 14:07:56 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

uint8_t				env_blt(t_registry *shell, char **av)
{
	int			ac;
	uint8_t		ret;

	ac = ft_tabsize(av);
	ret = SUCCESS;
	if (ac < 2)
		export_blt(shell, av);
	else
		ret = 2;
	return (ret);
}
